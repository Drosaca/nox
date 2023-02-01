## NOX
![](https://i.pinimg.com/originals/ec/55/c3/ec55c3048bb0562ef0bf64f7b8dff097.gif)

Simple program that detects when windows will shutdown and turn off your display 
#### Motivation
Displays are in sleep mode when the computer is off but my monitor blinks and emits way too much light in sleep mode. I am also too lazy to push the power button

### Usage

note1: the program will obviously act like a deamon to monitor the shutdown event. 
It hides the terminal if you click on it. 

```ps
nox.exe [screen_id] [screen_id] ...
```
the `screen_id` is a number between 0 and the number of monitors connected

note2: if no arguments are provided to the program all monitors will be powered off

## Run on startup
to run the program on startup you can write this on powershell

`$toclose` contains monitors ids that will be powered off, (the arguments of nox.exe) 


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
After restart if nox.exe is present on the process manager list it means that the program is working

note: if no arguments are provided to the program all monitors will be powered off 
