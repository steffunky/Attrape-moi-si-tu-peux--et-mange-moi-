#Attrape-moi si tu peux (Catch-me)


##The Game

The rules are simple: you have to crush your opponent.

Vous les règles par defaut sont du tour par tour, vous utilisez les 8 touches autour du
S pour vous deplacer, supposant que votre clavier soit AZERTY.

By disabling the turn based mode, the two players have a different set of keys, located right next to each other for additional fun !

The configuration file config.txt must be located in the same directory as the executable.
If not found, the program will fall back on its default values.

##Parameters customizable in config.txt:
 
|Variable   | Val. par défaut       | Description                          |   
| --------- |:---------------------:| ------------------------------------:|   
|NbLine     | Terminal's height - 3 | Number of lines                      |   
|NbCol      | Terminal's width /2 -1| Number of Columns                    |   
|XPosPlay1  | 0                     | Player 1's position on the X axis    |   
|YPosPlay1  | NbLine - 1            | Player 1's position on the Y axis    |   
|XPosPlay2  | NbCol - 1             | Player 2's position on the X axis    |   
|YPosPlay2  | 0                     | Player 2's position on the Y axis    |   
|inf_turns  | 0 (enabled)           | Unlimited number of turns            |   
|nb_turns   | 1                     | Maximum number of turns              |   
|tpt        | 1(enabled)            | Turn based Mode                      |   
|menu       | 0(diabled)            | Displays a menu at startup           |   
|ai         | 0(disabled)           | AI, only if tpt is set to 1          |   
|ailevel    | 0(easy)               | 0 = easy, 1 = impossible             |   
 
 Any parameter not found in the file will be set to its default value.
 
## How to compile

 Open a terminal, then    
 `git clone https://github.com/steffunky/Attrape-moi-si-tu-peux--et-mange-moi-.git`    
 `cd Attrape-moi-si-tu-peux--et-mange-moi-`    
 `make`    
 
 To play:    
 `./catch_me`    
 
