size="1920 1060"

function pirix
{
    xrdb -load $HOME/.Xresources
    xloadimage -onroot -fullscreen Pictures/wallpaper/mwm.jpg
    xclock &
    xosview &
    urxvt -geometry 80x40 -iconic &
#    smurf http://blackberry &
    mwm
}

case $app in
    amazon)
	openbox-lxde-pi &
	smurf a
	;;
    awesome)
	exec awesome
	;;
    chrome)
	openbox &
	chromium-browser
	;;
    comix)
	exec openbox &
	smurf c
	;;
    cmd)
	openbox-lxde-pi &
	$args
	;;
    dwm)
	exec dwm
	;;
    gnustep)
	exec wmaker
	;;
    google)
	openbox-lxde-pi &
	smurf g
	;;
    firefox)
	firefox-esr
	;;
    fvwm)
	fvwm
	;;
    pirix)
    motif)
	pirix
	;;
    netsurf)
	openbox &
	netsurf
	;;
    openbox)
	exec openbox-lxde-pi
	;;
    pixel)
	. /etc/X11/xinit/xinitrc
	;;
    remmina)
	openbox-lxde-pi &
	exec remmina
	;;
    soylentgreen)
	openbox-lxde-pi &
	vncviewer -useaddressbook SOYLENTGREEN
	;;
    surf)
	openbox-lxde-pi &
	surf http://startpage.com
	;;
    terminal)
	openbox &
	#x-terminal-emulator
	xterm -fullscreen
	;;
    webapps)
	openbox &
	surf http://localhost
	;;
    wikipedia)
	openbox &
	surf http://wikipedia.org
	;;
    xmonad)
	exec xmonad
	;;
    *)
	#. /etc/X11/xinit/xinitrc
	echo no app $app.
	sleep 4
	;;
esac
