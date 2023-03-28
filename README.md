<img width="150px" src="https://www.nscc.ca/img/aboutnscc/visual-identity-guidelines/artwork/nscc-jpeg.jpg" >

# PROG 2007 - Assignment 5
Input/Output, Files, Command Line Arguments and Dynamic Memory    
PROG 2007: Programming II  
**Due as posted in Brightspace**

## Important Notes
### Note 1:
Four sample input files have been provided to you in the starting GitHub repository in a subfolder named “test-files”. You may wish to COPY these into the “cmake-build-debug” folder to make your lives easier while developing the application. However, make sure NOT TO REMOVE THEM ENTIRELY FROM THE ORIGINAL FOLDER as that is where the tests require them to be.

### Note 2:
In order to get ANSI colors (mentioned below) showing in the CLion Run Console, we need to do the following routine:
1. Choose Help -> Edit Custom Properties from CLion menu
2. Add the following line to the idea.properties file:  
   *run.processes.with.pty=false*
3. Restart CLion.

Reference:
https://youtrack.jetbrains.com/issue/CPP-8395/Registry-setting-runprocesseswithpty-not-saved#focus=Comments-27-2499735.0-0

## Task
Write a C program that conforms to the requirements listed below.

### Requirements:
- You are building a terminal-based C version of the classic Wordle: Word of the Day Game: https://www.nytimes.com/games/wordle/index.html
- The game will use the ANSI colour routines to highlight guessed letters in the correct position in GREEN and guessed letters that are in a different position in the target word in YELLOW. The following link might be of help: https://www.theurbanpenguin.com/4184-2/
- Our game will be a bit different as we will not be constrained to 6 guesses at a 5-letter word. Our word size and guess limit will be read in from input files and dynamically set.
- You will be provided with 4 input files, each containing different settings for the **word size** and **maximum number of guesses** on the first line with the **solution or target word** on the second line of the file, like the following example which will have a word size of 5, number of guesses of 6 and a target word of 'SMOKY':  
  <img width="400px" src="https://prog2007.netlify.app/assign5-word1-file.png" alt="Assign 5 Word File One">  
- Read the first line and dynamically create/allocate a 2-dimensional character array of the appropriate size for the game board based on the word size and number of guesses, then populate the array with **reasonable starting characters**, such as the **underscore** that I have used in the examples below. **You should dynamically allocate the array in main.c and pass it into functions contained in wordle.c for game processing and/or game board display.**
- See the **General Game Play** section below for details on how the user actually plays the game
- When the player is done, write the game results (i.e. final game board state) to a new file with a line at the top showing whether they were successful or not. The output file will not contain coloured text. For example:  
  <img width="400px" src="https://prog2007.netlify.app/assign5-game-result1-file.png" alt="Assign 5 Game Result One">    
  <img width="400px" src="https://prog2007.netlify.app/assign5-game-result2-file.png" alt="Assign 5 Game Result Two">  

- The file names/paths for both the input and output  will be provided to the program via **command line arguments** (see the Examples below)


#### General Game Play:

1. Output the game board to the screen to start with enough spaces to indicate the target word length and enough rows to show the maximum number of guesses
2. Prompt the user to enter a guessed word
3. Validate the entry for correct length and make sure that it only contains letters (i.e. no digits or special characters). If it fails validation, print the appropriate message (although this does NOT need to go to **stderr** as we will not quit or error out on bad input). If the input was invalid, ask them to enter it again while not "charging" them for a guess nor updating the game board.
4. Output the game board again with the new guess added in the first empty row. The guess should show in **uppercase** no matter how it was entered. The game board should highlight in GREEN any guessed letters in the correct position in the target word and should highlight in YELLOW guessed letters that are in a different position in the target word.
5. If the guess is the not the same as the target **and** the user has not reached the maximum number of guesses, go back to Step 2. Otherwise, proceed to Step 6.
6. Tell the user if they have won the game or not (i.e. ultimately guessed the correct answer).

**NOTE**: Colour-coding double letters appropriately like actual Wordle does (i.e. if a letter exists twice in the guess but only once in the target, then only one letter would be colour-coded) is a bit beyond our scope but nice to have if you can get it to work.

**NOTE**: There is also NO requirement to make sure each "valid" entry is an actual dictionary word in English. As long as the entry is made up of the correct number of letters, then it will be considered valid (e.g. "ABCDE" will be considered a valid entry if trying to guess a 5-letter word) .

#### General requirements:

- You will need to put your function(s) to process game play (i.e. process guesses, output the colour-coded board results) in their  **own source file called wordle.c**
- Have all pre-processor definitions, any enumerations or struct definitions, & your function prototype declarations in a **header file called wordle.h**
- All your source files (i.e. main.c and wordle.c) should be in a **folder called “src”**
- Your header file (i.e. wordle.h) should be in a **folder called “inc”**
- Include clear comments
- Make sure your error messages output to **stderr**
- Maintain a standard layout/format for the code. Be consistent with spacing or tabbing, use the layout to make nested operation visually clear.
- Provide clear visual feedback to the user

### Sample Outputs:
Running Program with no Command Line Arguments:  
<img width="800px" src="https://prog2007.netlify.app/assign5-no-args.png" alt="Assign 5 No Command Line Arguments">

Running Program with wrong number of Command Line Arguments:  
<img width="800px" src="https://prog2007.netlify.app/assign5-bad-num-args.png" alt="Assign 5 Bad Number of Command Line Arguments">

Running Program with improper Command Line Arguments:  
<img width="800px" src="https://prog2007.netlify.app/assign5-bad-args.png" alt="Assign 5 Improper Command Line Arguments">

Running Program with bad Input File:  
<img width="800px" src="https://prog2007.netlify.app/assign5-bad-input-file.png" alt="Assign 5 Bad Input File">

Running Program with bad Output File:  
<img width="800px" src="https://prog2007.netlify.app/assign5-bad-output-file.png" alt="Assign 5 Bad Output File">

Running Program - Winning - Part One:  
<img width="800px" src="https://prog2007.netlify.app/assign5-success-part1.png" alt="Assign 5 Winning - Part One">

Running Program Winning - Part Two:  
<img width="800px" src="https://prog2007.netlify.app/assign5-success-part2.png" alt="Assign 5 Winning - Part One">

Running Program Losing:  
<img width="800px" src="https://prog2007.netlify.app/assign5-failure.png" alt="Assign 5 Losing">

Sample of bad Guess Input:  
<img width="800px" src="https://prog2007.netlify.app/assign5-invalid-guesses.png" alt="Assign 4 Bad Input">

Running Program with  Longer Word (6) - More Guesses(10):  
<img width="800px" src="https://prog2007.netlify.app/assign5-longer-word.png" alt="Assign 5 Longer Word - More Guesses">

## Submission Instructions
### Video Recording Submission:

You will demonstrate the completion of this project via a **video screen-capture recording** of you using CLion, GitBash, and viewing your code to show completion of the **Video Submission Checklist**, which is posted on Brightspace. You will post **either your video file or a link to it** (e.g. a Microsoft Stream recording, make sure to give the instructor permissions to watch it), to the Brightspace Assignment 5 Dropbox prior to the deadline. If you are not sure of how best to capture such a video, seek advice from the instructor prior to the deadline.

NOTE: MAKE SURE TO SHOW EVERYTHING IN THE VIDEO SUBMISSION CHECKLIST STEP-BY-STEP. YOU WILL NEED AUDIO IN THE VIDEO FOR AT LEAST THE CODE REVIEW PORTION OF THE CHECKLIST

> Written with [StackEdit](https://stackedit.io/).