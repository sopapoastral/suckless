/* See LICENSE file for copyright and license details. */

/* interval between updates (in ms) */
const unsigned int interval = 1000;

/* text to show if no value can be retrieved */
static const char unknown_str[] = "n/a";

/* maximum output string length */
#define MAXLEN 2048

/*
 * function            description                     argument (example)
 *
 * battery_perc        battery percentage              battery name (BAT0)
 *                                                     NULL on OpenBSD/FreeBSD
 * battery_remaining   battery remaining HH:MM         battery name (BAT0)
 *                                                     NULL on OpenBSD/FreeBSD
 * battery_state       battery charging state          battery name (BAT0)
 *                                                     NULL on OpenBSD/FreeBSD
 * cat                 read arbitrary file             path
 * cpu_freq            cpu frequency in MHz            NULL
 * cpu_perc            cpu usage in percent            NULL
 * datetime            date and time                   format string (%F %T)
 * disk_free           free disk space in GB           mountpoint path (/)
 * disk_perc           disk usage in percent           mountpoint path (/)
 * disk_total          total disk space in GB          mountpoint path (/)
 * disk_used           used disk space in GB           mountpoint path (/)
 * entropy             available entropy               NULL
 * gid                 GID of current user             NULL
 * hostname            hostname                        NULL
 * ipv4                IPv4 address                    interface name (eth0)
 * ipv6                IPv6 address                    interface name (eth0)
 * kernel_release      `uname -r`                      NULL
 * keyboard_indicators caps/num lock indicators        format string (c?n?)
 *                                                     see keyboard_indicators.c
 * keymap              layout (variant) of current     NULL
 *                     keymap
 * load_avg            load average                    NULL
 * netspeed_rx         receive network speed           interface name (wlan0)
 * netspeed_tx         transfer network speed          interface name (wlan0)
 * num_files           number of files in a directory  path
 *                                                     (/home/foo/Inbox/cur)
 * ram_free            free memory in GB               NULL
 * ram_perc            memory usage in percent         NULL
 * ram_total           total memory size in GB         NULL
 * ram_used            used memory in GB               NULL
 * run_command         custom shell command            command (echo foo)
 * swap_free           free swap in GB                 NULL
 * swap_perc           swap usage in percent           NULL
 * swap_total          total swap size in GB           NULL
 * swap_used           used swap in GB                 NULL
 * temp                temperature in degree celsius   sensor file
 *                                                     (/sys/class/thermal/...)
 *                                                     NULL on OpenBSD
 *                                                     thermal zone on FreeBSD
 *                                                     (tz0, tz1, etc.)
 * uid                 UID of current user             NULL
 * uptime              system uptime                   NULL
 * username            username of current user        NULL
 * alsa_master_vol     ALSA Master device volume       NULL
 * vol_perc            OSS/ALSA volume in percent      mixer file (/dev/mixer)
 *                                                     NULL on OpenBSD/FreeBSD
 * wifi_essid          WiFi ESSID                      interface name (wlan0)
 * wifi_perc           WiFi signal in percent          interface name (wlan0)
 */

const char*
alsa_master_vol_wrapper(const char * unused)
{
	(void)unused;
	return alsa_master_vol();
}

int
parse_int(const char* perc)
{
    int res = 0;

    for(int i = 0; *(perc + i); ++i)
    {
        res *= 10;
        res += (*(perc + i) - '0');
    }

    return res;
}

const char*
returnBatterySymbol()
{
    int perc = parse_int(battery_perc("BAT0"));
    if (battery_state("BAT0") != "+")
    {
        if (perc > 90)
            return "󰁹";
        if (perc > 80)
            return "󰂂";
        if (perc > 70)
            return "󰂁";
        if (perc > 60)
            return "󰂀";
        if (perc > 50)
            return "󰁿";
        if (perc > 40)
            return "󰁾";
        if (perc > 30)
            return "󰁽";
        if (perc > 20)
            return "󰁼";
        if (perc > 10)
            return "󰁻";
        if (perc > 0)
            return "󰁺";
    }
    else
    {
        if (perc == 100)
            return "󱈏";
        if (perc > 90)
            return "󰂅";
        if (perc > 80)
            return "󰂋";
        if (perc > 70)
            return "󰂊";
        if (perc > 60)
            return "󰢞";
        if (perc > 50)
            return "󰂉";
        if (perc > 40)
            return "󰢝";
        if (perc > 30)
            return "󰂈";
        if (perc > 20)
            return "󰂇";
        if (perc > 10)
            return "󰂆";
        if (perc > 0)
            return "󰢜";

    }
}

static const struct arg args[] = {
	/* function 	    format          			       argument */
    { returnBatterySymbol, "^c#67bc9c^%s "                            , NULL },
	{ battery_perc		 , "^c#e0def4^%s% ^c#ebbcba^│ "				  , "BAT0" },
	{ run_command     	 , "^c#9ccfd8^󰏖 ^c#e0def4^%s ^c#ebbcba^│ "    ,   "checkupdates | wc -l",  NULL },
	{ alsa_master_vol_wrapper, "^c#82a0d8^󱄠 ^c#e0def4^%s ^c#ebbcba^│ ",   NULL    },
	{ cpu_perc        	 , "^c#ebbcba^󰍛 %s%% "                        ,   NULL    },
	{ ram_used        	 , "^c#c4a7e7^ %s ^c#ebbcba^│ "              ,   NULL    },
	{ datetime        	 , "^c#f6c177^%s"                             ,   "^c#f6c177^󰃰 ^c#e0def4^%b %d ^c#f6c177^󱦟 ^c#e0def4^%k:%M "  },
};
