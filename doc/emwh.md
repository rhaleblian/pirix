Here’s the clean, citation‑grounded summary of **EWMH (Extended Window Manager Hints)** based on the canonical freedesktop.org specification.   [specifications.freedesktop.org](https://specifications.freedesktop.org/wm/latest/)

---

# ⭐ **Summary of EWMH (Extended Window Manager Hints)**  
**EWMH is a freedesktop.org standard that extends the older ICCCM rules to define how modern X11 window managers, applications, pagers, and taskbars communicate.** It provides a unified set of properties and protocols for desktops to support features like virtual desktops, window states, taskbars, docks, and compositing.

---

# 📘 What EWMH Is  
EWMH (sometimes called “NetWM”) is a **specification** that:

- Builds on the **ICCCM** (Inter‑Client Communication Conventions Manual)  
- Standardizes modern desktop behaviors that ICCCM never covered  
- Defines how **window managers**, **applications**, and **desktop utilities** (pagers, taskbars, docks) should interact  
- Uses a set of **_NET\*** properties on the X11 root window and application windows  

The goal is interoperability: any EWMH‑compliant WM can work with any EWMH‑aware application or panel.

---

# 🧩 Key Capabilities Defined by EWMH

## 1. **Window States & Actions**
Examples:
- `_NET_WM_STATE_FULLSCREEN`
- `_NET_WM_STATE_MAXIMIZED_VERT`
- `_NET_WM_STATE_HIDDEN` (minimized)
- `_NET_WM_ACTION_CLOSE`, `_NET_WM_ACTION_MOVE`, etc.

These allow apps and pagers to request state changes from the WM.

---

## 2. **Virtual Desktops / Workspaces**
EWMH standardizes:
- `_NET_NUMBER_OF_DESKTOPS`
- `_NET_CURRENT_DESKTOP`
- `_NET_DESKTOP_NAMES`

This is how pagers know what desktops exist and where windows live.

---

## 3. **Taskbars & Window Lists**
EWMH defines how taskbars discover:
- All windows (`_NET_CLIENT_LIST`)
- Their stacking order (`_NET_CLIENT_LIST_STACKING`)
- Their types (`_NET_WM_WINDOW_TYPE`)

This is why modern panels can show correct icons, titles, and states.

---

## 4. **Window Types**
Examples:
- `_NET_WM_WINDOW_TYPE_NORMAL`
- `_NET_WM_WINDOW_TYPE_DIALOG`
- `_NET_WM_WINDOW_TYPE_DOCK`
- `_NET_WM_WINDOW_TYPE_SPLASH`

This lets the WM treat docks, dialogs, and normal windows differently.

---

## 5. **Root Window Properties**
The WM publishes global desktop information on the root window:
- Supported hints (`_NET_SUPPORTED`)
- Desktop geometry
- Active window (`_NET_ACTIVE_WINDOW`)

---

## 6. **Compositing**
EWMH includes hooks for compositing managers:
- `_NET_WM_CM_Sn` (compositing manager selection)

This is how compositors like `picom` or `mutter` claim responsibility.

---

# 🏛️ Relationship to ICCCM  
ICCCCM defines *low‑level* X11 conventions (selections, WM protocols, focus, etc.).  
EWMH adds *modern desktop features* that ICCCM never addressed.

The spec explicitly states that WMs and clients **must still follow ICCCM** unless EWMH overrides it.   [specifications.freedesktop.org](https://specifications.freedesktop.org/wm/latest/)

---

# 🧠 Why EWMH Matters  
Without EWMH, you don’t get:

- Proper taskbars  
- Virtual desktops  
- Fullscreen/maximize behavior  
- Dock/panel integration  
- Compositing manager coordination  

Classic MWM predates EWMH entirely, which is why EMWM (the fork) adds partial EWMH support.

