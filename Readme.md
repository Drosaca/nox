## NOX

Simple program that detects when windows will shutdown and turn off your display 

to run the program on startup you can write this on powershell
```ps

$toclose = 1
mkdir $Env:Appdata\nox;cp nox.exe $Env:Appdata\nox;
$WshShell = New-Object -comObject WScript.Shell;
$Shortcut = $WshShell.CreateShortcut("$Env:Appdata\Microsoft\Windows\Start Menu\Programs\Startup\nox.lnk" );
$Shortcut.TargetPath = "$Env:Appdata\nox\nox.exe";
$Shortcut.Arguments = $toclose
$Shortcut.Save();
```