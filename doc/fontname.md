# Window Titlebar Font in EMWM (`Xresources`)

## Problem

The font defined in [`src/Xresources`](../src/Xresources) (`-adobe-helvetica-bold-o-normal--14-*`) was applied to menus, but not to window titlebars in `emwm`.

## Root Cause

1. **Legacy `fontList` vs. `renderTable`:**
   - [`src/Xresources`](../src/Xresources) originally only specified the legacy Motif `mwm` resource `*fontList` (and `*menubar*FontSet`):
     ```xresources
                                *fontList: -adobe-helvetica-bold-o-normal--14-*
                           *menu*fontList: -adobe-helvetica-bold-o-normal--14-*
                         *menubar*FontSet: -adobe-helvetica-bold-o-normal--14-*
     ```
   - Standard Motif widgets (such as the `XmRowColumn`, `XmPushButton`, and `XmLabelGadget` widgets `emwm` uses for menus and dialogs) still support the legacy `XmNfontList` (`fontList`) resource in `libXm`, so menus picked up `*fontList`.
   - Window frames, titlebars (`client` and `client.title`), icons (`icon`), and feedback (`feedback`) are drawn directly by `emwm` in [`DrawWindowTitle`](../../emwm/src/WmCDecor.c) and have their resources fetched manually via `XtGetSubresources` in [`ProcessAppearanceResources`](../../emwm/src/WmResource.c) using [`wmAppearanceResources`](../../emwm/src/WmResource.c).
   - Unlike traditional `mwm`, [`wmAppearanceResources`](../../emwm/src/WmResource.c) in `emwm` only defines `XmNrenderTable` (`renderTable`, class `RenderTable`) and does not read `fontList`.

2. **Motif `RenderTable` Rendition Requirements & Fallback:**
   - Because `emwm` is launched directly from `$HOME/Developer/emwm/src/emwm` without [`Emwm.ad`](../../emwm/src/Emwm.ad) installed into X11 `app-defaults`, `Emwm*title.renderTable: title` is not preloaded, and `wmAppearanceResources` defaults `renderTable` to `"Sans"`.
   - When `MakeAppearanceResources` in [`WmResource.c`](../../emwm/src/WmResource.c) checks `XmRenderTableGetDefaultFontExtents` and finds no valid rendition (`fontHeight == 0`), it logs:
     ```
     Title-bar render table contains no valid font information; using fallback font.
     ```
     and creates a fallback 12pt Xft `"Sans"` rendition.

## Solution

Configure `renderTable` and its rendition properties (`fontType` and `fontName`) in [`src/Xresources`](../src/Xresources):

```xresources
                        *renderTable: default
       *renderTable.default.fontType: FONT_IS_FONT
       *renderTable.default.fontName: -adobe-helvetica-bold-o-normal--14-*
```

- **`*renderTable: default`** assigns the `default` rendition tag to `emwm` appearance subparts (`client`, `client.title`, `icon`, `feedback`) and Motif widgets.
- **`*renderTable.default.fontType: FONT_IS_FONT`** specifies an X11 core/XLFD font (`FONT_IS_FONT` instead of `FONT_IS_XFT`). Without `fontType`, Motif leaves the rendition type as `XmAS_IS` and fails to load the font.
- **`*renderTable.default.fontName: -adobe-helvetica-bold-o-normal--14-*`** sets the XLFD font name for the rendition.
