## NOX

Simple program that detects when windows will shutdown and turn off your display 
#### Motivation
The displays are in sleep mode when the computer is off but my monitor blinks and emits way too much light in sleep mode, 
and I am too lazy to push the power button

### Usage

note1: the program will obviously act like a deamon to monitor the shutdown event and hides the terminal. So if nox.exe is present on the process manager list it means that the program is working 

```ps
nox.exe [screen_id] [screen_id] ...
```
the screen_id is a number between 0 and the number of monitors connected

note2: if no arguments are provided to the program all monitors will be powered off

## Run on startup
to run the program on startup you can write this on powershell

`$toclose` contains monitors ids that will be powered off 

the screen id is a number between 0 and the number of monitors connected

```ps

$toclose = 1
mkdir $Env:Appdata\nox;
cp nox.exe $Env:Appdata\nox;
$WshShell = New-Object -comObject WScript.Shell;
$Shortcut = $WshShell.CreateShortcut("$Env:Appdata\Microsoft\Windows\Start Menu\Programs\Startup\nox.lnk" );
$Shortcut.TargetPath = "$Env:Appdata\nox\nox.exe";
$Shortcut.Arguments = $toclose
$Shortcut.Save();
```

note: if no arguments are provided to the program all monitors will be powered off 
