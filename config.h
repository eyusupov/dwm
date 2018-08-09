/* vim: set noet ci pi sts=0 sw=4 ts=4 */
/* See LICENSE file for copyright and license details. */

/* appearance */
static const char *fonts[] = {
    "xft:Monospace:pixelsize=11:antialias=true:hinting=true",
    "xft:FontAwesome:pixelsize=11:antialias=true:hinting=true",
};

// Solarized
static const char *colorscheme[] = {
    "#073642", // black dark
    "#dc322f", // red dark
    "#859900", // green dark
    "#b58900", // yellow dark
    "#268bd2", // blue dark
    "#d33682", // magenta dark
    "#2aa198", // cyan dark
    "#eee8d5", // white dark
    "#002b36", // black light
    "#cb4b16", // red light
    "#586e75", // green light
    "#657b83", // yellow light
    "#839496", // blue light
    "#6c71c4", // magenta light
    "#93a1a1", // cyan light
    "#fdf6e3"  // white light
};

static const char dmenufont[] = "xft:Monospace:pixelsize=11:antialias=true:hinting=true";
static const char normbordercolor[] = "#444444";
static const char normbgcolor[]     = "#222222";
static const char normfgcolor[]     = "#bbbbbb";
static const char selbordercolor[]  = "#005577";
static const char selbgcolor[]      = "#005577";
static const char selfgcolor[]      = "#eeeeee";
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayspacing = 2;   /* systray spacing */
static const Bool systraypinningfailfirst = 1;   /* True: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const Bool showsystray       = 1;     /* False means no systray */
static const Bool showbar           = 1;     /* False means no bar */
static const Bool topbar            = 1;     /* False means bottom bar */

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "F1", "F2", "F3", "F4", "F5" };

// Use xprop to find out the class
static const Rule rules[] = {
	/* class      instance    title  tags mask isfloating   monitor */
	{ "Gimp",     NULL,       NULL,  0,        True,        1,     },
	{ "Skype",    NULL,       NULL,  1 << 4,   False,       0,     },
	{ "Pidgin",   NULL,       NULL,  0,        True,        0,     },
	{ "rdesktop", NULL,       NULL,  1 << 3,   True,        1,     },
	{ "PreVim",   NULL,       NULL,  0,        False,      -1,     },
	{ "Firefox",  NULL,       NULL,  1 << 2,   False,       1,     },
	{ "Telegram", NULL,       NULL,  1 << 5,   False,       0,     },
	{ "zoom",     NULL,       NULL,  1 << 6,   False,       0,     },
	{ "Slack",    NULL,       NULL,  1 << 7,   False,       0,     },
	{ "smplayer", NULL,       NULL,  0xff,     False,      -1,     },
};

/* layout(s) */
static const float mfact      = 0.65; /* factor of master area size [0.05..0.95] */
static const int nmaster      = 1;    /* number of clients in master area */
static const Bool resizehints = True; /* True means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", normbgcolor, "-nf", normfgcolor, "-sb", selbgcolor, "-sf", selfgcolor, NULL };

static Key keys[] = {
    	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_r,      spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY,                       XK_F12,    killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_F1,                     5)
	TAGKEYS(                        XK_F2,                     6)
	TAGKEYS(                        XK_F3,                     7)
	TAGKEYS(                        XK_F4,                     8)
	TAGKEYS(                        XK_F5,                     9)
  { MODKEY|ShiftMask,             XK_r,      self_restart,   {0} },
};

/* button definitions */
/* click can be ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
//	{ ClkWinTitle,          0,              Button1,        focusonclick,   {0} },
	{ ClkWinTitle,          0,              Button3,        zoom,           {0} },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

