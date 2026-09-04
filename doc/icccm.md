Below is a clean, accurate, citation‑grounded summary of **ICCCM**, based strictly on the canonical sources you’d expect (X.Org spec, Tronche’s HTML edition, and the Wikipedia overview). I’m keeping it tight, structured, and engineering‑useful.

---

# ⭐ **ICCCM (Inter‑Client Communication Conventions Manual) — Summary**  
**ICCCM is the foundational X11 standard that defines how X clients cooperate: selections (clipboard), cut buffers, window manager protocols, session management, shared resources, and color management.** It exists because X11 provides only mechanisms, not policies, so ICCCM establishes the conventions required for clients to interoperate correctly.   [Wikipedia](https://en.wikipedia.org/wiki/Inter-Client_Communication_Conventions_Manual)

---

# 📘 What ICCCM Is  
ICCCM is a **protocol‑level specification** (not a toolkit API) that defines how X clients should behave so they can coexist on the same X server. It covers:

- Clipboard/selection ownership  
- Window manager communication  
- Session management  
- Shared resource negotiation (colormaps, focus, etc.)  
- Cut buffers (legacy)  

It was originally written by David Rosenthal (MIT X Consortium) and released with X11R4 (1989), with Version 2.0 released in X11R6 (1994).   [Wikipedia](https://en.wikipedia.org/wiki/Inter-Client_Communication_Conventions_Manual)

---

# 🧩 Core Areas of ICCCM

## 1. **Selections (Clipboard Model)**
ICCCM defines:
- How a client **owns** a selection (PRIMARY, SECONDARY, CLIPBOARD)  
- How other clients **request** the selection  
- How large transfers work (INCR mechanism)  
- Target atoms and conversion rules  

This is the basis for X11 copy/paste behavior.   [X.Org](https://x.org/releases/X11R7.6/doc/xorg-docs/specs/ICCCM/icccm.html)

---

## 2. **Cut Buffers (Legacy)**
Before selections were standardized, X11 used “cut buffers” — fixed properties on the root window.  
ICCCM documents them for compatibility but selections supersede them.   [X.Org](https://x.org/releases/X11R7.6/doc/xorg-docs/specs/ICCCM/icccm.html)

---

## 3. **Window Manager Interaction**
ICCCM defines how clients and the WM coordinate:

- `WM_PROTOCOLS` (e.g., `WM_DELETE_WINDOW`)  
- `WM_NORMAL_HINTS` (size, aspect ratio, resize increments)  
- `WM_COLORMAP_WINDOWS`  
- Focus and input models  

This is the low‑level contract that all WMs must follow.   [Wikipedia](https://en.wikipedia.org/wiki/Inter-Client_Communication_Conventions_Manual)

---

## 4. **Session Management**
ICCCM defines conventions for:

- Saving/restoring client state  
- Interaction with session managers (`WM_SAVE_YOURSELF`)  

This is why older X11 desktops could restore sessions.   [Tcler's Wiki](https://wiki.tcl-lang.org/page/ICCCM)

---

## 5. **Shared Resources**
ICCCM covers how clients negotiate:

- Colormap installation  
- Color allocation  
- Keyboard focus  
- Other shared X11 resources  

This prevents clients from fighting over hardware‑level resources.   [Wikipedia](https://en.wikipedia.org/wiki/Inter-Client_Communication_Conventions_Manual)

---

# 🏛️ ICCCM’s Role in the Modern Stack
- ICCCM is **mandatory** for correct X11 behavior.  
- EWMH (Extended Window Manager Hints) **builds on ICCCM** and adds modern desktop features (workspaces, docks, fullscreen, etc.).  
- EWMH explicitly states that clients **must still follow ICCCM** unless EWMH overrides it.   [Wikipedia](https://en.wikipedia.org/wiki/Inter-Client_Communication_Conventions_Manual)

---

# ⚠️ Known Issues & Criticism
- ICCCM is often considered **ambiguous** and difficult to implement correctly.  
- Some parts are obsolete (e.g., cut buffers).  
- Many early WMs and toolkits were only partially compliant.  
- Modern toolkits (GTK, Qt, Motif, Tk) hide most ICCCM details from application developers.   [Wikipedia](https://en.wikipedia.org/wiki/Inter-Client_Communication_Conventions_Manual)

---

# 🧭 Bottom Line
ICCCM is the **low‑level interoperability contract** for X11 clients.  
It defines how selections, window management, session management, and shared resources work.  
Everything else — including EWMH, compositing, modern desktops — is layered on top of it.
