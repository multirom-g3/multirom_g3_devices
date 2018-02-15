/*
 * This file contains device specific hooks.
 * Always enclose hooks to #if MR_DEVICE_HOOKS >= ver
 * with corresponding hook version!
 */

#include <stdint.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>

#include <private/android_filesystem_config.h>

#include <errno.h>
#include <fcntl.h>
#include <log.h>
#include <signal.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <util.h>

#if MR_DEVICE_HOOKS >= 1
int mrom_hook_after_android_mounts(const char *busybox_path, const char *base_path, int type)
{
    return 0;
}
#endif /* MR_DEVICE_HOOKS >= 1 */

#if MR_DEVICE_HOOKS >= 2
void mrom_hook_before_fb_close(void)
{
}
#endif /* MR_DEVICE_HOOKS >= 2 */

#if MR_DEVICE_HOOKS >= 3
static int read_file(const char *path, char *dest, int dest_size)
{
    int res = 0;
    FILE *f = fopen(path, "r");
    if(!f)
        return res;

    res = fgets(dest, dest_size, f) != NULL;
    fclose(f);
    return res;
}

static void set_cpu_governor(void)
{
    size_t i;
    char buff[256];
    static const char *governors[] = { "interactive", "ondemand" };

    if(!read_file("/sys/devices/system/cpu/cpu0/cpufreq/scaling_governor", buff, sizeof(buff)))
        return;

    if(strncmp(buff, "performance", 11) != 0)
        return;

    if(!read_file("/sys/devices/system/cpu/cpu0/cpufreq/scaling_available_governors", buff, sizeof(buff)))
        return;

    write_file("/sys/module/msm_thermal/core_control/enabled", "0");
    write_file("/sys/devices/system/cpu/cpu1/online", "1");
    write_file("/sys/devices/system/cpu/cpu2/online", "1");
    write_file("/sys/devices/system/cpu/cpu3/online", "1");

    for(i = 0; i < sizeof(governors)/sizeof(governors[0]); ++i)
    {
        if(strstr(buff, governors[i]))
        {
            write_file("/sys/devices/system/cpu/cpu0/cpufreq/scaling_governor", governors[i]);
            write_file("/sys/devices/system/cpu/cpu1/cpufreq/scaling_governor", governors[i]);
            write_file("/sys/devices/system/cpu/cpu2/cpufreq/scaling_governor", governors[i]);
            write_file("/sys/devices/system/cpu/cpu3/cpufreq/scaling_governor", governors[i]);
            break;
        }
    }

    write_file("/sys/module/lpm_levels/enable_low_power/l2", "4");
    write_file("/sys/module/msm_pm/modes/cpu0/power_collapse/suspend_enabled", "1");
    write_file("/sys/module/msm_pm/modes/cpu1/power_collapse/suspend_enabled", "1");
    write_file("/sys/module/msm_pm/modes/cpu2/power_collapse/suspend_enabled", "1");
    write_file("/sys/module/msm_pm/modes/cpu3/power_collapse/suspend_enabled", "1");
    write_file("/sys/module/msm_pm/modes/cpu0/power_collapse/idle_enabled", "1");
    write_file("/sys/module/msm_pm/modes/cpu1/power_collapse/idle_enabled", "1");
    write_file("/sys/module/msm_pm/modes/cpu2/power_collapse/idle_enabled", "1");
    write_file("/sys/module/msm_pm/modes/cpu3/power_collapse/idle_enabled", "1");
    write_file("/sys/module/msm_pm/modes/cpu0/standalone_power_collapse/suspend_enabled", "1");
    write_file("/sys/module/msm_pm/modes/cpu1/standalone_power_collapse/suspend_enabled", "1");
    write_file("/sys/module/msm_pm/modes/cpu2/standalone_power_collapse/suspend_enabled", "1");
    write_file("/sys/module/msm_pm/modes/cpu3/standalone_power_collapse/suspend_enabled", "1");
    write_file("/sys/module/msm_pm/modes/cpu0/standalone_power_collapse/idle_enabled", "1");
    write_file("/sys/module/msm_pm/modes/cpu1/standalone_power_collapse/idle_enabled", "1");
    write_file("/sys/module/msm_pm/modes/cpu2/standalone_power_collapse/idle_enabled", "1");
    write_file("/sys/module/msm_pm/modes/cpu3/standalone_power_collapse/idle_enabled", "1");
    write_file("/sys/module/msm_pm/modes/cpu0/retention/idle_enabled", "1");
    write_file("/sys/module/msm_pm/modes/cpu1/retention/idle_enabled", "1");
    write_file("/sys/module/msm_pm/modes/cpu2/retention/idle_enabled", "1");
    write_file("/sys/module/msm_pm/modes/cpu3/retention/idle_enabled", "1");
    write_file("/sys/module/msm_thermal/core_control/enabled", "1");
    write_file("/sys/devices/system/cpu/cpufreq/interactive/io_is_busy", "1");

    write_file("/sys/devices/system/cpu/cpufreq/interactive/above_hispeed_delay", "20000 1400000:40000 1700000:20000");
    write_file("/sys/devices/system/cpu/cpufreq/interactive/go_hispeed_load", "90");
    write_file("/sys/devices/system/cpu/cpufreq/interactive/hispeed_freq", "1497600");
    write_file("/sys/devices/system/cpu/cpufreq/interactive/target_loads", "85 1500000:90 1800000:70");
    write_file("/sys/devices/system/cpu/cpufreq/interactive/min_sample_time", "40000");
    write_file("/sys/module/cpu_boost/parameters/boost_ms", "20");
    write_file("/sys/module/cpu_boost/parameters/sync_threshold", "1728000");
    write_file("/sys/devices/system/cpu/cpufreq/interactive/sampling_down_factor", "100000");
    write_file("/sys/module/cpu_boost/parameters/input_boost_freq", "1497600");
    write_file("/sys/module/cpu_boost/parameters/input_boost_ms", "40");
}

void tramp_hook_before_device_init(void)
{
    // G3's kernel has "performance" as default
    set_cpu_governor();
}
#endif /* MR_DEVICE_HOOKS >= 3 */

#if MR_DEVICE_HOOKS >= 4
int mrom_hook_allow_incomplete_fstab(void)
{
    return 1;
}
#endif

#if MR_DEVICE_HOOKS >= 5
void mrom_hook_fixup_bootimg_cmdline(char *bootimg_cmdline, size_t bootimg_cmdline_cap)
{
}

int mrom_hook_has_kexec(void)
{
    // shamu kernels don't have /proc/config.gz, but they
    // have CONFIG_PROC_DEVICETREE enabled by default, so check
    // for /proc/device-tree/soc/kexec_hardboot-hole instead
    // (the DTB node that reserves memory for kexec-hardboot page).

    static const char *checkfile = "/proc/device-tree/soc/kexec_hardboot-hole";
    if(access(checkfile, R_OK) < 0)
    {
        ERROR("%s was not found!\n", checkfile);
        return 0;
    }
    return 1;
}
#endif

#if MR_DEVICE_HOOKS >= 6
static int fork_and_exec(char **cmd, char** env)
{
    pid_t pID = fork();
    if(pID == 0)
    {
        stdio_to_null();
        setpgid(0, getpid());
        execve(cmd[0], cmd, env);
        ERROR("Failed to exec %s: %s\n", cmd[0], strerror(errno));
        _exit(127);
    }
    return pID;
}

static int qseecomd_pid = -1;

void tramp_hook_encryption_setup(void)
{
    // start qseecomd
    char* cmd[] = {"/mrom_enc/qseecomd", NULL};
    char* env[] = {"LD_LIBRARY_PATH=/mrom_enc", NULL};

    // setup links and permissions based on TWRP's
    remove("/firmware");
    remove("/vendor");
    symlink("/mrom_enc/firmware", "/firmware");
    symlink("/mrom_enc/vendor", "/vendor");
    chmod("/dev/qseecom", 0660);
    chown("/dev/qseecom", AID_SYSTEM, AID_DRMRPC);
    chmod("/dev/ion", 0664);
    chown("/dev/ion", AID_SYSTEM, AID_SYSTEM);
    chmod("/mrom_enc/adbd", 0777);
    chmod("/mrom_enc/busybox", 0777);
    chmod("/mrom_enc/qseecomd", 0755);
    qseecomd_pid = fork_and_exec(cmd, env);
    if (qseecomd_pid == -1)
        ERROR("Failed to fork for qseecomd; should never happen!\n");
    else
        INFO("qseecomd started: pid=%d\n", qseecomd_pid);
}

void tramp_hook_encryption_cleanup(void)
{
    struct stat info;
    if (qseecomd_pid != -1)
    {
        kill(-qseecomd_pid, SIGTERM); // kill the entire process group
        waitpid(qseecomd_pid, NULL, 0);
    }
    INFO("cleaned up after qseecomd\n");

    remove("/firmware");
    remove("/vendor");
}

void mrom_hook_fixup_full_cmdline(char *bootimg_cmdline, size_t bootimg_cmdline_cap)
{
}
#endif
