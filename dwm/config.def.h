/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */

/* Bar padding parameters*/
static const int vertpad            = 0;       /* vertical padding of bar */
static const int sidepad            = 0;       /* horizontal padding of bar */

/*Gap parameters*/
static const unsigned int gappih    = 5;        /* horiz inner gap between windows */
static const unsigned int gappiv    = 5;        /* vert inner gap between windows */
static const unsigned int gappoh    = 5;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 5;       /* vert outer gap between windows and screen edge */
static       int smartgaps          = 0;        /* 1 means no outer gap when there is only one window */

/*Bar parameters*/
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const int user_bh            = 15;        /* 2 is the defauls spacing around the bar's font */

/*Fonts*/
static const char *fonts[]          = { "SymbolsNerdFont:size=12:antialias=true", "Mononoki Nerd Font Mono:size=13:antialias=true", "Noto Sans CJK JP:size=12:antialias=true" };
static const char dmenufont[]       = "Mononoki Nerd Font Mono:size=13";

/* Rose Pine Colors*/

static const char col_base[]        = "#191724";
static const char col_surface[]     = "#1f1d2e";
static const char col_overlay[]     = "#26233a";
static const char col_muted[]       = "#6e6a86";
static const char col_subtle[]      = "#908caa";
static const char col_text[]        = "#e0def4";
static const char col_love[]        = "#eb6f92";
static const char col_gold[]        = "#f6c177";
static const char col_rose[]        = "#ebbcba";
static const char col_pine[]        = "#31748f";
static const char col_foam[]        = "#9ccfd8";
static const char col_iris[]        = "#c4a7e7";
static const char col_hlow[]        = "#21202e"; /*Highlight Low */
static const char col_hmed[]        = "#403d52"; /*Highlight Med */
static const char col_hhig[]        = "#524f67"; /*Highlight High*/

/*Colors*/
static const char col_gray1[]       = "#1a1b26"; /* "#222222" */
static const char col_gray2[]       = "#565f89"; /* "#444444" */
static const char col_gray3[]       = "#cfc9c2"; /* "#bbbbbb" */
static const char col_gray4[]       = "#e0def4"; /* "#eeeeee" */
static const char col_cyan[]        = "#31748f"; /* "#005577" */
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm]  =	 { col_gray3, col_gray1,  col_gray2  },
	[SchemeSel]   =	 { col_gray4, col_cyan,   col_cyan   },
	[SchemeWarn]  =	 { col_base,  col_gold,   col_love   },
	[SchemeUrgent]=	 { col_text,  col_love,   col_love   },
    [SchemeTitle] =  { col_gray4, col_gray1,  col_gray1  },
};

/* tagging */
// static const char *tags[] = { "", "󰈹", "󰭹", "󰉋", "", "󰥠", "", "", "" };
static const char *tags[] = { "", "󰖟", "󰭹", "󰉋", "", "󰥠", "", "", "" };

/*Underline focus parameters*/
static const unsigned int ulinepad	= 0;	    /* horizontal padding between the underline and tag */
static const unsigned int ulinestroke	= 0;	/* thickness / height of the underline */
static const unsigned int ulinevoffset	= 0;	/* how far above the bottom of the bar the line should appear */
static const int ulineall 		= 0;	        /* 1 to show underline on all tags, 0 for just the active ones */

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class              instance    title       tags mask     isfloating   monitor */
	{ "Gimp"            , NULL,       NULL,       0,            1,           -1 },
	{ "Firefox"         , NULL,       NULL,       1 << 8,       0,           -1 },
    { "gnome-calculator", NULL,       NULL,       0,            1,           -1 }, // <-- dk si funciona (name: gnome-calculator)
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

#define FORCE_VSPLIT 1  /* nrowgrid layout: force two clients to always split vertically */
#include "vanitygaps.c"

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "[M]",      monocle },
	{ "[@]",      spiral },
	{ "[\\]",     dwindle },
	{ "H[]",      deck },
	{ "TTT",      bstack },
	{ "===",      bstackhoriz },
	{ "HHH",      grid },
	{ "###",      nrowgrid },
	{ "---",      horizgrid },
	{ ":::",      gaplessgrid },
	{ "|M|",      centeredmaster },
	{ ">M>",      centeredfloatingmaster },
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ NULL,       NULL },
};

/* key definitions */
// Mod1Maks = Alt Mod4Mask = Super
#define MODKEY Mod1Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },
#define STACKKEYS(MOD,ACTION) \
	{ MOD, XK_j,     ACTION##stack, {.i = INC(+1) } }, \
	{ MOD, XK_k,     ACTION##stack, {.i = INC(-1) } }, \
	{ MOD, XK_grave, ACTION##stack, {.i = PREVSEL } }, \
	{ MOD, XK_q,     ACTION##stack, {.i = 0 } }, \
	{ MOD, XK_a,     ACTION##stack, {.i = 1 } }, \
	{ MOD, XK_z,     ACTION##stack, {.i = 2 } }, \
	{ MOD, XK_x,     ACTION##stack, {.i = -1 } },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_base, "-nf", col_text, "-sb", col_pine, "-sf", col_surface, NULL };
static const char *termcmd[]  = { "urxvt", NULL };

static const Key keys[] = {
	/* modifier                     key           function        argument */
	{ MODKEY,                       XK_d,         spawn,          SHCMD("dmenu_run -nf '#e0def4' -sf '#e0def4'") },
	{ MODKEY,                       XK_Return,    spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_b,         togglebar,      {0} },
	STACKKEYS(MODKEY,                             focus)
	STACKKEYS(MODKEY|ShiftMask,                   push)
	{ MODKEY,                       XK_i,         incnmaster,     {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_d,         incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,         setmfact,       {.f = -0.05} },
    { MODKEY,                       XK_l,         setmfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask,             XK_h,         setcfact,       {.f = +0.25} },
	{ MODKEY|ShiftMask,             XK_l,         setcfact,       {.f = -0.25} },
	{ MODKEY|ShiftMask,             XK_o,         setcfact,       {.f =  0.00} },
	{ MODKEY|ShiftMask,             XK_Return,    zoom,           {0} },
	{ MODKEY|Mod4Mask,              XK_u,         incrgaps,       {.i = +1 } },
	{ MODKEY|Mod4Mask|ShiftMask,    XK_u,         incrgaps,       {.i = -1 } },
	{ MODKEY|Mod4Mask,              XK_i,         incrigaps,      {.i = +1 } },
	{ MODKEY|Mod4Mask|ShiftMask,    XK_i,         incrigaps,      {.i = -1 } },
	{ MODKEY|Mod4Mask,              XK_o,         incrogaps,      {.i = +1 } },
	{ MODKEY|Mod4Mask|ShiftMask,    XK_o,         incrogaps,      {.i = -1 } },
	{ MODKEY|Mod4Mask,              XK_6,         incrihgaps,     {.i = +1 } },
	{ MODKEY|Mod4Mask|ShiftMask,    XK_6,         incrihgaps,     {.i = -1 } },
	{ MODKEY|Mod4Mask,              XK_7,         incrivgaps,     {.i = +1 } },
	{ MODKEY|Mod4Mask|ShiftMask,    XK_7,         incrivgaps,     {.i = -1 } },
	{ MODKEY|Mod4Mask,              XK_8,         incrohgaps,     {.i = +1 } },
	{ MODKEY|Mod4Mask|ShiftMask,    XK_8,         incrohgaps,     {.i = -1 } },
	{ MODKEY|Mod4Mask,              XK_9,         incrovgaps,     {.i = +1 } },
	{ MODKEY|Mod4Mask|ShiftMask,    XK_9,         incrovgaps,     {.i = -1 } },
	{ MODKEY|Mod4Mask,              XK_0,         togglegaps,     {0} },
	{ MODKEY|Mod4Mask|ShiftMask,    XK_0,         defaultgaps,    {0} },
	{ MODKEY,                       XK_Tab,       view,           {0} },
	{ MODKEY,                       XK_q,         killclient,     {0} },
	{ MODKEY,                       XK_u,         setlayout,      {.v = &layouts[10]} },
	{ MODKEY,                       XK_y,         setlayout,      {.v = &layouts[3]} },
	{ MODKEY,                       XK_t,         setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_r,         setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_e,         setlayout,      {.v = &layouts[11]} },
	{ MODKEY,                       XK_space,     setlayout,      {.v = &layouts[1]} },
	{ MODKEY|ShiftMask,             XK_space,     togglefloating, {0} },
	{ MODKEY,                       XK_0,         view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,         tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,     focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period,    focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,     tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period,    tagmon,         {.i = +1 } },
	TAGKEYS(                        XK_1,                          0)
	TAGKEYS(                        XK_2,                          1)
	TAGKEYS(                        XK_3,                          2)
	TAGKEYS(                        XK_4,                          3)
	TAGKEYS(                        XK_5,                          4)
	TAGKEYS(                        XK_6,                          5)
	TAGKEYS(                        XK_7,                          6)
	TAGKEYS(                        XK_8,                          7)
	TAGKEYS(                        XK_9,                          8)
	{ MODKEY|ShiftMask,             XK_BackSpace, quit,           {0} },
	{ MODKEY|ControlMask|ShiftMask, XK_q,         quit,           {1} },
	{ MODKEY|ShiftMask,             XK_s,         spawn,          SHCMD("~/.local/bin/sysstate") },
	{ MODKEY|ShiftMask,             XK_v,         spawn,          SHCMD("~/.local/bin/volume") },
	{ MODKEY|ShiftMask,             XK_b,         spawn,          SHCMD("~/.local/bin/backlight") },
	{ MODKEY|ShiftMask,             XK_s,         spawn,          SHCMD("~/.local/bin/screenshot") },
	{ MODKEY|ShiftMask,             XK_l,         spawn,          SHCMD("~/.local/bin/language") },
	{ MODKEY|ControlMask|ShiftMask, XK_s,         spawn,          SHCMD("flameshot gui") },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

