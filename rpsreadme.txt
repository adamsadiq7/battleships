Hello Ian

This is my rock, paper scissors program

To run you compile with "gcc -std=c99 rps.c -0 rps"
You will then run the program with no arguments, "./rps"
The program will then autotest automatically, and if the tests pass, it will start the game by referring to the startGame function.

THe program will greet you to the game, and it will ask if you want more than 10 games with the computer, this is so the program will know how many characters to read when inputting 1 or 2 digit numbers
you will type (y/n) for >= 10 games or <10 games.
Then you can finally input the amount of games you want with the computer

Once entered it will show you the options

1 = Rock
2 = Paper
3 = Scissors

Then you will play against the computer.
The program works by the computer running a random integer from 1-3, and by that it will be equated to the corresponding options. It will compare your input with the computer and sn, lose or draw by using a logic function. (Took your advice to use much more functions). It returns if the user won the point or not and adds the scores accordingly. It checks if the game is finished after every round, and if so it uses short functions to give feedback to the user, (again I used more functions so the program looked more structured)



