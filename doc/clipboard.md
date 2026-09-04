copy-and-paste over RDP to MWM doesn't work.  is this mismatch between RDP and X11 clipboards, and can it be fixed?

**Short answer:** No — **emwm does *not* attempt to fix Motif/X11 clipboard semantics or bridge PRIMARY↔CLIPBOARD**, and therefore it does *not* solve the RDP clipboard mismatch. Its goals are Xinerama, Xrandr, UTF‑8/Xft, and partial EWMH support — *not* modernizing Motif’s clipboard model.   [Github](https://github.com/alx210/EMWM)

Below is the deeper, engineering‑grade breakdown.

---

# 🧩 What EMWM *does* and *does not* change

## ✅ EMWM modernizes MWM in these areas
From the project README and documentation, EMWM adds:  
- **Xinerama support**  
- **Xrandr support**  
- **UTF‑8/Xft font rendering**  
- **Relevant EWMH hints** (window states, workspaces, etc.)  
  [Github](https://github.com/alx210/EMWM)

These are *window‑manager* features: screen layout, decorations, hints, fonts.

## ❌ EMWM does **not** modify:
- ICCCM selection handling  
- Motif clipboard behavior  
- PRIMARY/CLIPBOARD synchronization  
- Any mechanism for bridging Windows RDP clipboard to X11 selections  

There is **no mention** in the README, FAQ, or commit history of clipboard‑related enhancements. The EMWM FAQ/Guide focuses on X resources, fonts, workspaces, and EWMH — *not* clipboard or selection management.   [fastestcode.org](https://fastestcode.org/misc/emwm-guide.html)

---

# 🧠 Why EMWM cannot fix the RDP clipboard mismatch

Clipboard behavior in X11 is **not** a window‑manager responsibility. It is handled by:

- The **client application** (Motif apps often only set PRIMARY)  
- The **X server** (selection ownership)  
- Optional **clipboard managers** (parcellite, clipit, etc.)  

MWM/EMWM simply does not participate in selection ownership or translation.  
So even a modernized fork like EMWM cannot fix:

- Motif apps writing only to PRIMARY  
- RDP expecting CLIPBOARD  
- No automatic PRIMARY→CLIPBOARD sync  

This is why copy/paste still fails under EMWM unless you add a clipboard bridge.

---

# 🛠️ Practical fix (still required under EMWM)

You still need a **selection synchronizer** inside the X11 session:

### Option A — xclip loop
```bash
while true; do
    xclip -o -selection primary | xclip -i -selection clipboard
    sleep 0.1
done
```

### Option B — clipboard manager
- `parcellite --daemon`
- `clipit`
- `xfce4-clipman`

These keep PRIMARY and CLIPBOARD in sync so RDP can see the copied text.

---

# 🧭 Bottom line
- **EMWM does not attempt to fix clipboard issues.**  
- **Clipboard bridging is still required**, exactly as with classic MWM.  
- The RDP mismatch is architectural (Windows clipboard vs. X11 selections), not a window‑manager bug.

If you want, I can produce a **systemd user service** that automatically runs a Motif‑friendly clipboard bridge on login, or a **zero‑overhead xclip daemon** tuned for your workflow.
