;Ryan Garaffa
;March 8 2022
;Ramapo College of New Jersey
;Organizational Programming Langauges


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;Basic functions
;Function Name: printWelcome
;Purpose:Prints a nice welcome blob of text
;Parameters: None
;Return Value:None
;Algorithym: None
;Assistance Recieved: None
(defun printWelcome ()
	(print "Welcome To Canoga - Developed and Designed by Ryan Garaffa")
	(print "This project was created for my Organizational Programming Langauges class at Ramapo College")
	(print "Total Time Spent on this was Approximately 52 hours")
	(terpri)
  )

;Function Name: _Replace
;Purpose: To Replace an element from a list with another element
;Parameters:
;		l -> list
;		ele -> element to replace
;		newele -> the new element that will take ele's place
;Return Value: List with element replaced
;Algorithym: cycles through list until ele = the first in the l, then it just returns the newele + the rest of the list
;Assistance Recieved: None
(defun _Replace (l ele newele) ;The list, the element to be replaced, what you want to replace it with  
	(cond ( (eq (first l) ele)
		(append (cons newele nil) (rest l) ) 
	      ) ; base case
	      ( (= 1 1)
		(append (cons (first l) nil) (_Replace (rest l) ele newele) ) 
              ) ; Recursive Case
	);closes cond
);closes defun

;Function Name: _Replace
;Purpose: To Replace an element from a list with its location in the list (for uncovering)
;Parameters:
;               l -> list
;               place -> element to replace's location
;               count -> a count, will replace the element with the count
;Return Value: List with element replaced
;Algorithym: cycles through list until place = count, then it just returns the count + the rest of the list
;Assistance Recieved: None
(defun _ReplaceX (l place count) ;list, 
	;(print count);For Debugging
	(cond ( (eq count place)
                (append (cons count nil) (rest l) )
              ) ; base case
	      ( (equal (rest l) ())
	        () ) ;
              ( (= 1 1)
                (append (cons (first l) nil) (_ReplaceX (rest l) place (+ count 1) ) )
              ) ; Recursive Case
        );closes cond
);closes defun

;Function Name: _Find
;Purpose: To Find an element in a list
;Parameters:
;               l -> list
;               ele -> element to find
;               
;Return Value: element if found, or nil
;Algorithym: cycles through list until ele = the first in the l, then it just returns the element, 
;if the list is empty, it returns nil
;Assistance Recieved: None
(defun _Find (l ele)
	(cond
		((eq ele (first l))
		ele)
		((equal (rest l) ())
		nil);Add Base case for not found
		((= 1 1)
		(_Find (rest l) ele))
	);closes cond
);closes defun

;Function Name: _FindLoc
;Purpose: To Find the Location of an element in the list
;Parameters:
;               l -> list
;               ele -> element to find
;               count -> will keep track of place in list 
;Return Value: location of the element or nil if not found
;Algorithym: cycles through list until ele = the first in the l, then it just returns the element or nil
;Assistance Recieved: None
(defun _FindLoc (l ele count)
        (cond
                ((eq ele (first l))
                count)
                ((equal (rest l) ())
                nil);Add Base case for not found
                ((= 1 1)
                (_FindLoc (rest l) ele (+ count 1)) )
        );closes cond
);closes defun

;Function Name: _Remove
;Purpose: To Remove an element from a list
;Parameters:
;               l -> list
;               ele -> element to remove
;               
;Return Value: List with element removed
;Algorithym: cycles through list until ele = the first in the list, then it just returns rest of the list. 
;by using cons and recursion, we get the full list with just the one element removed
;Assistance Recieved: We did something similar in class 
(defun _Remove (l ele) ; element and list
	(cond
		( (null l)
		() ) ;Base Case
		( (equal ele (first l))
		(rest l) ) ; Second Base Case
		
		( (= 1 1)
		(cons (first l) (_Remove (rest l) ele)) );Recursive Case

	);closes cond
);closes defun

;Function Name: _RemoveX
;Purpose: To Remove an element from a list based off location
;Parameters:
;               l -> list
;               eleNum -> element to remove's location
;		count -> current count/location
;Return Value: List with element removed
;Algorithym: cycles through list until ele = the first in the list, then it just returns rest of the list.
;by using cons and recursion, we get the full list with just the one element removed
;Assistance Recieved: None
(defun _RemoveX (l eleNum count)
        (cond ( (eq count eleNum)
                (rest l )
              ) ; base case
              ( (= 1 1)
                (append (cons (first l) nil) (_RemoveX (rest l) eleNum (+ count 1) ) )
              ) ; Recursive Case
        );closes cond
);closes defun

;Function Name: GetHigh
;Purpose: To get the highest value from a list
;Parameters:
;               l -> list
;               
;
;Return Value: The highest value in the lits
;Algorithym: cycles through list and returns the max of the first in the list 
;versus a recursive call using the rest of the list, this compares all the values and returns the max.
;Assistance Recieved: None
(defun GetHigh(l) ; list of numbers
	(cond 
		((null l)
		0) ; base case
		((= 1 1)
		(max (GetHigh (rest l)) (first l) )) ;

	);closes cond
);closes defun

;Function Name: GetSecondHigh
;Purpose: To get the second highest value from a list
;Parameters:
;               l -> list
;
;
;Return Value: The second highest value in the list
;Algorithym: Send it to SecondHigh to do the work
;Assistance Recieved: None
(defun GetSecondHigh (l)
		(SecondHigh l l)	
);closes defun

;Function Name: SecondHigh
;Purpose: To get the second highest value from a list
;Parameters:
;               l -> list
;		l2 -> copy of list
;
;Return Value: The second highest value in the list
;Algorithym: if l and l2 are equal, we get rid of the first highest, 
;then we just recurse like GetHigh to get the second highest
;Assistance Recieved: None
(defun SecondHigh (l l2)
	(cond
		((null l)
		0);base case

		((equal l l2);will get rid of the highest element in the list
		(SecondHigh (_Remove l (GetHigh l)) l2));recurse

		((= 1 1)
		(max (SecondHigh (rest l) l2) (first l)));recurse

	);closes cond
);closes defun

;Function Name: GetThirdHigh
;Purpose: To get the third highest value from a list
;Parameters:
;               l -> list
;
;
;Return Value: The third highest value in the list
;Algorithym: Send it to ThirdHigh to do the work
;Assistance Recieved: None
(defun GetThirdHigh (l)
	(ThirdHigh l l l)
);closes defun

;Function Name: ThirdHigh
;Purpose: To get the third highest value from a list
;Parameters:
;               l -> list
;               l2 -> copy of list
;		l3 -> copy of list
;Return Value: The third highest value in the list
;Algorithym: if l and l3 are equal, we get rid of the first highest,
;if l and l2 are equal, we get rid of the second highest,
;then we just recurse like GetHigh to get the third highest
;Assistance Recieved: None
(defun ThirdHigh (l l2 l3)
	(cond
		((null l)
		0)
		
		((equal l l3) ;will get rid of the first high
		(ThirdHigh (_Remove l (GetHigh l)) (_Remove l2 (GetHigh l2)) l3))

		((equal l l2);will get rid of the second high
		(ThirdHigh (_Remove l (GetHigh l)) l2 l3))

		((= 1 1);will recurse
		(max (ThirdHigh (rest l) l2 l3) (first l)))

	);closes cond
);closes defun

;Function Name: HasNumber
;Purpose: To tell us if the list has a number
;Parameters:
;               l -> list
;               
;
;Return Value: 1 for true and 0 for false
;Algorithym: we cycle through the list and return 1 if the first element is an integer, else return 0
;Assistance Recieved: None
(defun HasNumber (l)
	(cond
		((typep (first l) 'integer);if we have an integer
		1)
		((equal l ());if we have empty list
		0)
		((= 1 1);else recurse
		(HasNumber (rest l)) )
	);closes cond
);closes defun

;Function Name: AddAll
;Purpose: To get the sum of all the elements in the list
;Parameters:
;               l -> list
;                                 
;
;Return Value: the sum of all the elements in the list
;Algorithym: we cycle through the list and recursively add the first elements
;Assistance Recieved: None
(defun AddAll(l) ; list of numbers to add
	(cond
		((null l)
		0)

		((= 1 1)
			(+
			(first l)
			(AddAll (rest l))
			)
		)
	);closes cond
);closes defun






;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;DICE CODE

;Global variable that will hold values of dice rolls for a loaded save
(defvar Rolls nil)

;Function Name: RollOneDice
;Purpose: To roll a single die 
;Parameters: None
;               
;                                 
;
;Return Value: a random number from 1 to 6   
;Algorithym: we use rand
;Assistance Recieved: None
(defun RollOneDice()
	;(print
	(+ (random 6) 1)
	;);closes print
)

;Function Name: RollTwoDice
;Purpose: To roll two dice        
;Parameters: None
;                        
;                
;
;Return Value: a random number from 2 to 12
;Algorithym: we use RollOneDice twice and add                                                                           
;Assistance Recieved: None
;Will Roll TWO DICE
(defun RollTwoDice()
	(print
	(+ (RollOneDice) (RollOneDice))
	)
)

;Function Name: RollDice
;Purpose: To roll dice appropriately               
;Parameters: 
;            player -> 0 for human and 1 for computer            
;            numDice -> 1 or 2 for number of dice
;
;Return Value: a random number from 2-12
;Algorithym: we announce the player and then we call the appropriate roll_Dice function                                                                
;Here we also check if there are dice rolls to be read
;Assistance Recieved: None
(defun RollDice(player numDice)
	;(print "First Rolls:")
	;(print (first Rolls))
	(cond
		( (eq player 0) ; Human Player
		(print "Human Rolled: ") )
		( (eq player 1) ;com player
		(print "Computer Rolled: ") )
	) ; closes cond
	
	(cond	
		((Not (equal Rolls ()) );There are Rolls to Be Read
		(let*
			(
			;let variable
			(toPlay (AddAll (first Rolls)))
			)
			;let body
			(setq Rolls (rest Rolls))
			(print toPlay)
			toPlay
		))

		((eq numDice 1) ;will Roll one dice
		(RollOneDice))
		((eq numDice 2) ;will Roll two dice
		(RollTwoDice) )	

	);closes cond
);closes defun Roll









;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;BOARD CODE
;Function Name: ReadBoardSize
;Purpose: To allow the player to choose the board size               
;Parameters: None
;                        
;                
;
;Return Value: a number holding a valid board size ->9-11
;Algorithym: we read from the user and validate the input                                                   
;Assistance Recieved: Design similar to example on website
(defun ReadBoardSize ()
	(print "Please Enter a number in the range 9-11 for the board size: ")
	(terpri)
	(ValidSize (read))  
);closes defun

;Function Name: ValidSize
;Purpose: Check the Board Size validity               
;Parameters: 
;            num -> input number            
;                
;
;Return Value: a valid number from 9 to 11
;Algorithym: we check if the number is out of bounds and the data type                                           
;Assistance Recieved: Design similar to example on website
(defun ValidSize (num)
  (cond 
	( (Not (typep num 'integer))
	  (print "Please enter an integer")
	  (ReadBoardSize) )
	( ( < num 9 )
          (ReadBoardSize)  )
        ( ( > num 11 )
          (ReadBoardSize)  )
        ( t num )
   ) 
)

;Function Name: CreateNewBoardSide
;Purpose: To create a fresh side of a board           
;Parameters: 
;            size -> holds size of the board            
;                
;
;Return Value: a fresh list with numbers 1-size
;Algorithym: we check what the size is and then return the appropriate list                                                      
;Assistance Recieved: None
(defun CreateNewBoardSide (size)
  (cond ( (= size 9)
        (list 1 2 3 4 5 6 7 8 9) )
       ( (= size 10)
        (list 1 2 3 4 5 6 7 8 9 10) )
       ( (= size 11)
        (list 1 2 3 4 5 6 7 8 9 10 11) )
   ))


;UnUsed
;(defun Cover(side ele)
;	(print "Covering: ")
;	(print ele)
;	(_Replace side ele '*) 
; )

;Function Name: CoverFromList
;Purpose: To cover numbers on a side of the board from a list               
;Parameters: 
;            side -> side of the board            
;            toCover -> list of numbers to cover   
;
;Return Value: the side of the board with the appropriate numbers covered
;Algorithym: We check if the number is playable, and then replace it with a '* if so and recurse
;if the toCover is empty, we return the covered side, we also have an error check here 
;Assistance Recieved: None
(defun CoverFromList (side toCover);side and list of numbers to cover
	(cond
		((equal toCover ());check if toCover is empty
		side);base case

		( (eq (first toCover) (_Find side (first toCover)) );will check if number is playable
		(CoverFromList 
			(_Replace side (first toCover) '*) 
			(rest toCover) 
		))
		
		((= 1 1)
		(print "Error in CoverFromList function, number is unplayable"))
	);closes cond

);closes defun

;UnUsed
;(defun Uncover(side ele)
;	(print "Uncovering: ")
;       (print ele)
;        (_ReplaceX side ele 1)   ; COME BACK
; )

;Function Name: UncoverFromList
;Purpose: To uncover numbers on a side of the board from a list
;Parameters:
;            side -> side of the board
;            toUncover -> list of numbers to cover
;
;Return Value: the side of the board with the appropriate numbers covered
;Algorithym: We check if the number is playable, and then replace it with a its place in the list, if so and recurse
;if the toUncover is empty, we return the uncovered side, we also have an error check here
;Assistance Recieved: None
(defun UncoverFromList (side toUncover);side and list of numbers to Uncover

        (cond
                ((equal toUncover ());check if toCover is empty
                side);base case

                ( (= 1 1);(eq (_FindLoc side '* 1) (first toUncover) );will check if number is playable
                (UncoverFromList
                        (_ReplaceX side (first toUncover) 1)
                        (rest toUncover)
                ))

                ((= 1 1)
                (print "Error in UncoverFromList function, number is unplayable")
		(print (first toUncover)))
        );closes cond

);closes defun

;UnUsed -> replaced with _Find
;Will Check if element is in list returns the location within list -> returns -1 if not in list
;(defun CheckElement(l ele count)
;	(cond
;		( (eq ele (first l))
;		(return-from CheckElement count)) ; base case
;		((eq () (rest l))
;		(return-from CheckElement -1)) ; second base case
;		( ()
;		(CheckElement (rest l) ele count) )
;	)
;
;)

;Function Name: DisplayBoard
;Purpose: To Display the current board in a neat and consistent fashion
;Parameters:
;            H -> list of Human's side
;            C -> list of computer's side
;	     FT -> first turn value
;Return Value: None
;Algorithym: We output some headers and print appropriate data
;Assistance Recieved: None
(defun DisplayBoard(H C FT);Hside, Cside, FirstTurn
	(print "Computer: ")
	(print C)
	(print "Human: ")
	(print H)
	(print "First Turn: ")
	(cond	((eq FT 0)
		(print 'Human))
		((eq FT 1)
		(print 'Computer))

	);closes cond
	(terpri)

);closes defun






;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;LOADING FROM SAVE

;Function Name: LoadSave
;Purpose: To ask the user if they would like to load a save
;Parameters: None
;            
;            
;
;Return Value: 1 for yes or 0 for no
;Algorithym: We print and read from the user, send read to ValidLoadSave
;Assistance Recieved: None
;Will Load From a Save - will return 1 for yes and 0 for no
(defun LoadSave ()
  (print "Would you like to load from a save? Enter 'y' for yes or 'n' for no: ")
  (terpri) ; new line
  (ValidLoadSave(read))
  )

;Function Name: ValidLoadSave
;Purpose: To validate user input
;Parameters:
;            char -> user input
;            
;
;Return Value: 1 for yes and 0 for no
;Algorithym: We check if the input is equal to y or n and assign our value appropriately, else recurse
;Assistance Recieved: None
(defun ValidLoadSave (char)
  (cond ( (eq char 'y) ; returns 1 for yes
         1)
        ( (eq char 'n) ; returns 0 for no
         0)
        ( (= 1 1) ; "Else" recursively call LoadSave Promt
         (LoadSave) )
        )
  )

;Function Name: ReadSave
;Purpose: To collect needed data from the save
;Parameters:
;            filename -> file to read from
;            
;
;Return Value: the filedata in a list format
;Algorithym: We open and read the file
;Assistance Recieved: None
(defun ReadSave (filename)
	(with-open-file (stream filename)
		(read stream)
	);closes with-open-file

);close defun

;Function Name: InterpretLoadSave
;Purpose: To see if the file data was read properly, useful for debugging
;Parameters:
;            fileData -> data from file
;
;
;Return Value: None
;Algorithym: We interpret the file data using firsts and rests and print it
;Assistance Recieved: None
(defun InterpretLoadSave (fileData)
	(let*
		;variable
		(
		(C (first fileData))
		(H (first (rest fileData)))
		(fturn (first (rest (rest fileData))))
		(nturn (first (rest (rest (rest fileData)))))
		(DiceRolls (first (rest (rest (rest (rest fileData))))))
		)
		
		;let body
		(print "C:")
		(print C)
		(print "H:")
		(print H)
		(print "fturn")
		(print fturn)
		(print "nturn")
                (print nturn)
		(print "Dice Rolls")
		(print DiceRolls)


	);closes let*
)

;NOT FINISHED
;Function Name: SaveGame
;Purpose: To save the game to a file
;Parameters:
;            input -> reads in yes or no to save question
;
;
;Return Value: nil, will exit
;Algorithym: None
;Assistance Recieved: None
(defun SaveGame (input)
	(cond
		((eq input 'y) ;will save game
		(print "Save feature is not yet implemented"))

		((eq input 'n) ;will continue game
		nil)

		((= 1 1)
		(print "Would you like to save the game? Please enter y for yes or n for no")
		(SaveGame(read)))

	);closes cond
);closes defun









;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;GAME CODE
;Function Name: Begin
;Purpose: To play out the first round of the game and send all needed data to PlayGame
;Parameters:
;            load -> 1 if we want to load, else = 0
;
;
;Return Value: nil
;Algorithym: Will Check if we want to load a Save, 
;if so, we will collect input for a filename, will read in the data, and 
;then send everything into the turns. We will then recieve a score from 
;CalcScore calling the appropriate turn function and then use that to add 
;to scores from file. Finally we check to see who won and send all 
;necessary data to PlayGame
;If we do not want to load a save, we get the first turn and send that to 
;the round function which will return a score. Based off that score, we 
;can announce the winner and send ourselves to PlayGame
;Assistance Recieved: None
(defun Begin (load)
	(cond 
		((= load 1) ;Will Run Code for Loaded Save
		(print "Please enter the name of the file you would like to load in ALL LOWERCASE -> ex = lispsave.txt")
		(terpri)
		(let*
			;variable
			(
			;reads from file
			(filename (read))
			(filedata (ReadSave filename))
			(C (first filedata))
	                (H (first (rest fileData)))
	                (fturn 
				(cond 
					((eq (first (rest (rest fileData))) 'Computer)
					1)
					((eq (first (rest (rest fileData))) 'Human)
                                        0)
					(()
					(print "Error in Reading first Turn, will set to human")
					0)
				)
			)
	                (nturn 
				(cond 
                                        ((eq (first (rest (rest (rest fileData)))) 'Computer)
                                        1)
                                        ((eq (first (rest (rest (rest fileData)))) 'Human)
                                        0)
					((= 1 1)
					(print "Error in reading next turn, will set to human")
					0)
                                )
			)
	                (DiceRolls (setq Rolls (first (rest (rest (rest (rest fileData))))))) 
			
			;Plays out rest of Round -> passes the next turn, HSide, CSide, fturn, and turn count of 2
			(Score (CalcScore (PlayTurn nturn (first H) (first C) fturn 4)))
			);closes variables

			;let* body
			(cond
                                ((> Score 0);Score is positive and therefore human won and recieves score
                                (print "Human has won the round and Earned: ")
                                (print Score)
                                (print "Points!")
				;	    Score won + HScore,    CScore Loaded,   winner, fturn, HandicapNum
                                (PlayGame (+ Score (first (rest H))) (first (rest C)) 0 fTurn (CalcHandicapNum Score)))

                                ((< Score 0);Score is negative and therefore comp won and recieves score
                                (print "Computer has won the round and Earned: ")
                                (print (* Score -1))
                                (print "Points!")
				;	   HScore loaded,   Cscore loaded + score earned, winner, fturn, handicapnum
                                (PlayGame (first (rest H)) (+ (* -1 Score) (first (rest C))) 1 fTurn (CalcHandicapNum (* -1 Score))))

                                ((= 1 1)
                                (print "The Round has ended in a Draw")
                                (PlayGame (first (rest H)) (first (rest C)) 2 fTurn (CalcHandicapNum Score)))
                        );closes cond and let* body


		)) ;closes let* and conditional
        
		((= load 0)
		(let* (
			;variables
			(fTurn (GetFTurn))
			( Score(PlayRound fTurn (ReadBoardSize) 2 0) )
		      )

			;body of let
			(cond
				((> Score 0);Score is positive and therefore human won and recieves score
				(print "Human has won the round and Earned: ")
				(print Score)
				(print "Points!")
				(PlayGame Score 0 0 fTurn (CalcHandicapNum Score)))
				
				((< Score 0);Score is negative and therefore comp won and recieves score
				(print "Computer has won the round and Earned: ")
                                (print (* Score -1))
                                (print "Points!")
				(PlayGame 0 (* -1 Score) 1 fTurn (CalcHandicapNum (* -1 Score) )))
			
				((= 1 1)
				(print "The Round has ended in a Draw")
				(PlayGame 0 0 2 fTurn (CalcHandicapNum Score)))
			)
		)

		) ; Will run code not from a loaded save

	);closes cond
);closes defun

;Function Name: CalcHandicapNum
;Purpose: To calculate the handicap number from a score
;Parameters:
;            score -> score from round
;
;
;Return Value: an appropriate handicap number
;Algorithym: We divide Score by 10 and module Score by ten and then add the sum of those two numbers.
;Assistance Recieved: None
(defun CalcHandicapNum (Score)
	(let*
		(;variables
			(SinglesDigit (mod Score 10))
			(TensDigit (/ (- Score SinglesDigit) 10))
		)
		(+ TensDigit SinglesDigit)

	);closes let
);

;Function Name: PlayGame
;Purpose: To Play the Game after the first round
;Parameters:
;		HScore -> Human Score
;		CScore -> Computer Score
;		Winner -> winner from previous round
;		fTurn -> First turn from previous round
;		HandicapNum -> Number to be covered for next handicap
;Return Value: nil, will recurse
;Algorithym: We check for keepPlaying
;Then We print the current scores
;Then we apply the appropriate handicap
;Then based off the score returned, we
;Announce the winner and recurse
;If we do not want to keep playing, 
;we announce the winner and exit
;Assistance Recieved: None
(defun PlayGame (HScore CScore Winner fTurn HandicapNum);Winner&fTurn-> 0=Human 1=Comp

	(PrintScores HScore CScore)

	(cond
		((= 1 (KeepPlaying))				;Will check if we want to keep playing

		(let* (
                        ;variable
                        ( Score 
			(cond
				((= fTurn 1)		;if Computer went first -> com is handicapped
				(PlayRound(GetFTurn) (ReadBoardSize) 1 HandicapNum))
				
				((= fTurn 0)		;if Human went first -> Human is handicapped
				(PlayRound (GetFTurn) (ReadBoardSize) 0 HandicapNum))

			);closes cond
			);defines Score
                      )

                        ;body of let
                        (cond
                                ((> Score 0);Score is positive and therefore human won and recieves score
				(print "Human has won the round and Earned: ")
                                (print Score)
                                (print "Points!")
                                (PlayGame (+ Score HScore) CScore 0 (GetFTurn) (CalcHandicapNum Score)))

                                ((< Score 0);Score is negative and therefore comp won and recieves score
				(print "Computer has won the round and Earned: ")
                                (print (* Score -1))
                                (print "Points!")
				(PlayGame HScore (+ (* -1 Score) CScore) 1 (GetFTurn) (CalcHandicapNum (* -1 Score) )))
				
				((= Score 0)
				(print "The Round has ended in a draw")
				(PlayGame HScore CScore 2 (GetFTurn) (CalcHandicapNum Score)))
                        )
                ))


		((= 1 1)					;We will not keep playing
		(cond
			((> HScore CScore)
			(print "Congratulations! Human Player has Won!")
			(PrintScores HScore CScore)
			)

			((= HScore CScore)
			(print "The Game has ended in a Draw...")
			(PrintScores HScore CScore)
			)

			((= 1 1)
			(print "The Computer has won. Good luck next time.")
			(PrintScores HScore CScore)
			)

		));closes inner cond and conditional  ->  Announce Winner and final Scores
	);closes cond

);closes defun

;Function Name: Print Scores
;Purpose: To print the scores
;Parameters:
;            HScore -> human score
;	     CScore -> Computer Score
;
;Return Value: nil
;Algorithym: Prints headers and scores
;Assistance Recieved: None
(defun PrintScores (HScore CScore)
	(print "Human's Score: ")
        (print HScore)
        (print "Computer's Score: ")
        (print CScore)
)

;Function Name: KeepPlaying
;Purpose: To see if human wants to continue
;Parameters: None
;            
;
;
;Return Value: 1 for yes and 0 for no
;Algorithym: prints questions and validates input
;Assistance Recieved: None
(defun KeepPlaying ()
	(print "Would you like to continue playing? Enter y for yes or n for no")
	(ValidKeepPlaying (read));will validate either a y or n
);closes defun

;Function Name: ValidKeepPlaying
;Purpose: To validate keep playing input
;Parameters:
;            char -> reads input
;
;
;Return Value: nil, will exit
;Algorithym: Will check if we read a y or n and if not, recurse, if so, return 1 for y and 0 for n
;Assistance Recieved: None
(defun ValidKeepPlaying (char)
  (cond ( (eq char 'y) ; returns 1 for yes
         1)
        ( (eq char 'n) ; returns 0 for no
         0)
        ( (= 1 1) ; "Else" recursively call KeepPlaying Prompt
         (KeepPlaying) )
  )
)

;Function Name: GetFTurn
;Purpose: To Roll the Dice for the first turn
;Parameters: None
;            
;
;
;Return Value: nil
;Algorithym: Creates values RH and RC for human and computer rolls
;if they are equal, we recurse, else we let whoever rolled higher go first
;0 for human and 1 for computer
;Assistance Recieved: None
(defun GetFTurn ()
	(let 
		(;variable
		(RH (RollDice 0 2))
		(RC (RollDice 1 2))
		) 

		(cond
			((= RH RC);If Both rolls are equal
			(print "Since there was a tie, we shall reroll")
			(GetFTurn));
			( (> RH RC);If Human rolls higher 
			(HumanGoesFirst) )
			((= 1 1);else
			(CompGoesFirst))

		); closes cond
	);closes let
)

;Function Names: HumanGoesFirst and CompGoesFirst
;Purpose: To print a neat header and return appropriate number
;Parameters: None
;            
;
;
;Return Value: 0 for human and 1 for computer
;Algorithym: print a header and return appropriate number
;Assistance Recieved: None
(defun HumanGoesFirst()
	(print "Human Will Go First")
	0
)
(defun CompGoesFirst()
	(print "Computer Will Go First")
	1
)






;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;ROUND CODE
;Function Name: PlayRound
;Purpose: To play a round of the game
;Parameters:
;		fTurn -> first turn
;		BSize -> board Size
;		P -> player to be handicapped
;		HandicapNum -> number to be covered
;Return Value: Score value, negative for computer
;Algorithym: We create a new board with handicap if applicable
;We call PlayTurn using our created board and fTurn 
;PlayTurn is nested within CalcScore so we just return score
;Assistance Recieved: None
(defun PlayRound (fTurn BSize P HandicapNum) ;first turn, boardsize, player to be handicapped, handicapNum
	(let* (
		;(BSize (ReadBoardSize))
		(HSide 
			(cond
				((= P 1)
				(print "Giving Handicap to Computer, covering")
				(print HandicapNum)
				(ApplyHandicap
					(CreateNewBoardSide BSize)
					HandicapNum
				));closes ApplyHandicap and conditional

				((= 1 1) ;else
				(CreateNewBoardSide BSize))

			)
		) ;Creates Human Board Side
		
		(CSide 
			(cond
				((= P 0)
				(print "Giving Handicap to Human, covering ")
				(print HandicapNum)
				(ApplyHandicap
					(CreateNewBoardSide BSize)
					HandicapNum
				));closes ApplyHandicap and conditional

				((= 1 1) ;else
                                (CreateNewBoardSide BSize))

			);closes cond
		) ;Creates Computer Board Side
	     )

		;Let Body
		(cond	
			((= 1 1)
			(CalcScore
			(PlayTurn fTurn HSide CSide fturn 0);Play Turn
			));closes CalcScore and conditional
		);closes cond
	);closes let
) ; closes defun

;Function Name: ApplyHandicap
;Purpose: Applys Handicap to a side
;Parameters:
;		S -> Side
;		Num -> Number to be covered
;Return Value: list holding the new board side with applied handicap
;Algorithym: We check if the number is on the side
;if so, then we just cover it and return
;if its not we check for an error
;Else we recurse with Num - 1
;(Recurse is necessary in the case someone scores 66 where handicapNum > 11)
;Assistance Recieved: None
(defun ApplyHandicap (S Num)
	(cond
		((eq (_Find S Num) Num);if number is on side
		(CoverFromList S (cons Num nil))) ;base case

		((< Num 1);Error case
		(print "Error in ApplyHandicap")
		(print "Applying No Handicap")
		S)
		
		((> Num (length S))
		(ApplyHandicap S (- Num 1)));recurse
	);closes cond
);closes defun

;Function Name: CheckWon
;Purpose: To Check if a player has won the round
;Parameters:
;		P -> PlayerSide
;		O -> OpponentSide
;		tCount -> turn counter
;Return Value: 1 if player has won, 0 if not
;Algorithym: We check if its the first turn
;if so, player can only win by covering
;else we check if P has all *'s
;else we check if O has all numbers
;else we return 0
;Assistance Recieved: None
(defun CheckWon (P O tCount);PSide and OSide and turn counter
	(cond
		((= tCount 0)		;disallows a player to win on the first turn
		(cond
			((Not (eq (HasNumber P) 1)) ;player can still win by covering
			1)

			((= 1 1) ;but cannot win by uncovering
			0)
		);closes cond
		);closes conditional
		
		( (Not (eq (HasNumber P) 1));check if PSide has all X's
		1)

		((Not (eq (_Find O '*) '*));check id OSide does not have any X's
		1)

	        ((= 1 1)
		0)					;;ComeBack
	);closes cond
);closes defun

;Function Name: CalcScore
;Purpose: To Calculate the score earned in a round
;Parameters:
;            B -> holds board in fashion ((HSide) (CSide))
;
;
;Return Value: Score (negative if computer won)
;Algorithym: 
;Check if H won by covering -> if so we Add the uncovered squares on CSide
;Check if C won by covering -> if so we Add the uncovered squares on HSide * -1
;Check if H won by uncovering -> if so we Add the covered squares on CSide
;Check if C won by uncovering -> if so we Add the covered squares on HSide * -1
;else throws an error
;Assistance Recieved: None
(defun CalcScore (B); will read in the board in the format ((HSide) (CSide))
	(cond
		((= (HasNumber (first B)) 0)			;will check if HSide does not have a number (HSide won by covering)
		(print "Human won by covering")
		(AddUnC (first (rest B))))

		((= (HasNumber (first (rest B))) 0)		;will check if CSide does not have a number (CSide won by covering)
		(print "Computer won by covering")
		(* -1 (AddUnC (first B))))

		((Not (eq (_Find (first B) '*) '*) )		;will check if HSide does not have an '* (Computer won by uncovering)
		(print "Computer won by uncovering")
		(* -1 (AddC (first (rest B)))))
		
		((Not (eq (_Find (first (rest B)) '*) '*) )	;will check if CSide does not have an '* (Human won by uncovering)
		(print "Human won by uncovering")
		(AddC (first B)))

		((= 1 1)
		(print "Error Calculating Score"))

	);closes cond
);closes defun

;Function Name: AddUnC
;Purpose: Add up all numbers that are uncovered on a side
;Parameters:
;               S -> Side
;               
;		
;Return Value: sum of uncovered numbers
;Algorithym: Add all the numbers from ExtractPlayable function
;Assistance Recieved: None
(defun AddUnC (S) ;read in a Side
	(AddAll (ExtractPlayable S 1))
)

;Function Name: AddC  
;Purpose: Add up all numbers that are covered on a side
;Parameters:
;               S -> Side
;                                
;
;Return Value: sum of covered numbers     
;Algorithym: Add all the numbers from ExtractPlayable function 
;Assistance Recieved: None
(defun AddC (S) ;reads in a side
	(AddAll (ExtractPlayable S 0))
)







;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;TURN CODE
;Function Name: PlayTurn
;Purpose: Display Board and send to appropriate PlayTurn function (H or C)
;Parameters:
;		player -> current player
;		HSide -> Hside of the board
;		CSide -> CSide of the board
;		fTurn -> first turn of the round
;Return Value: list -> ((HSide) (CSide))     
;Algorithym: checks player value and sends to appropriate function
;Assistance Recieved: None
(defun PlayTurn (player HSide CSide fturn tCount) ;Reads in player and Board to call functions appropriately. And turn counter
	(DisplayBoard HSide CSide fturn)
	(cond	
		((eq player 1); 1 represents computer
		(PlayTurnC HSide CSide fturn tCount)) ;Will Play Turn for Computer
		((eq player 0); 0 represents human
		(PlayTurnH HSide CSide fturn tCount)) ; Will Play Turn for Human

	) ; closes cond
); closes defun

;Function Name: PlayTurnH
;Purpose: Play out a turn for a human player
;Parameters:
;               HSide -> Humans Side
;		CSide -> Computer Side
;		fturn -> first turn of round
;		tCount -> turn counter for round
;Return Value: list -> ((HSide) (CSide))
;Algorithym: 
;Check if player wants to save -> if so send to Save function
;Check if player has won -> if so return list of board
;Set Variuables ->
;R = Roll, covDec = cover decision, NumToPlay = Numbers to Play
;These Values are derived from Select functions
;Check if player lost their turn -> if so call PlayTurn passing 1 as the player
;Else Calls PlayTurn passing 0 as player for human to roll again 
;Board is also passed appropriately to PlayTurn
;Assistance Recieved: None
(defun PlayTurnH (HSide CSide fturn tCount)
	(print "Would you like to save and exit? Please enter y for yes or n for no")
	(SaveGame (read))
	(cond
		((eq (CheckWon HSide CSide tCount) 1);Will check if human has won
		(print "Human player has won the round")
		(list HSide CSide)) ;Will return appropriate list of the board
		
		;Will run if human has not won
		((= 1 1)
		(let* (
			;variables	
			(R (RollDice 0 (SelectNumDice HSide)) );holds roll value
			(covDec (SelectCovDec R HSide CSide)) ; holds cover decision
			(NumToPlay (SelectNumbersToPlay R HSide CSide covDec))		
		      )

			;Let Body
			(cond
				((eq covDec nil);Error Check
				(print "Player has lost their Turn")
				(PlayTurn 1 HSide CSide fturn (+ tCount 1));returns current board state Computer plays next
				)				

                                ((= covDec 2);Turn is lost and no move is made
				(print "Player has lost their turn.")
                                (PlayTurn 1 HSide CSide fturn (+ tCount 1)));returns current board state Computer plays next

                                ( (equal NumToPlay () );Turn Is lost and no move is made
                                (PlayTurn 1 HSide CSide fturn (+ tCount 1)));returns current board state Computer plays next

                                ((eq covDec 1);Will Check if we want to cover
                                (PlayTurn 0 (CoverFromList HSide NumToPlay) CSide fturn tCount))
				;Will Cover Appropriate numbers

                                ((eq covDec 0)
                                (PlayTurn 0 HSide (UncoverFromList CSide NumToPlay) fturn tCount))
				;Will Uncover Appropriate numbers

                                ((= 1 1)
                                (print "Error In body of PlayTurnH"))

                        );closes cond
		));closes let and conditional
	);closes cond
);close defun

;Function Name: PlayTurnC
;Purpose: Play out a turn for a computer player
;Parameters:
;               HSide -> Humans Side
;               CSide -> Computer Side
;               fturn -> first turn of round
;               tCount -> turn counter for round
;Return Value: list -> ((HSide) (CSide))
;Algorithym:
;Check if player has won -> if so return list of board
;Set Variuables ->
;R = Roll, covDec = cover decision, NumToPlay = Numbers to Play
;These Values are derived from Select functions
;Check if player lost their turn -> if so call PlayTurn passing 0 as the player (for human)
;Else Calls PlayTurn passing 1 as player for computer to roll again
;Board is also passed appropriately to PlayTurn
;Assistance Recieved: None
(defun PlayTurnC (HSide CSide fturn tCount)
	(cond
		((eq (CheckWon CSide HSide tCount) 1) ;Will check if a player has won
		(print "Computer player has won the round")
		(list HSide CSide)) ;Will return the board


		;Will run if computer has not won
		((= 1 1)
		(let* (	
			;variables
			(R (RollDice 1 (SelectNumDice CSide)) ) ; holds Roll value
			(covDec (SelectCovDecC R HSide CSide)) ;holds cover decision
			(NumToPlay (SelectNumbersToPlayC R HSide CSide covDec));holds a list of numbers to play
		      )
			;body
			(cond
				((= covDec 2);Turn is lost and no move is made
				(PlayTurn 0 HSide CSide fturn (+ tCount 1)));returns current board state Human plays next

				( (equal NumToPlay () );Turn Is lost and no move is made
				(PlayTurn 0 HSide CSide fturn (+ tCount 1)));returns current board state Human plays next
			
				((eq covDec 1);Will Check if we want to cover
				(PlayTurn 1 HSide (CoverFromList CSide NumToPlay) fturn tCount))
				;Will Cover Appropriate numbers
	
				((eq covDec 0)
				(PlayTurn 1 (UncoverFromList HSide NumToPlay) CSide fturn tCount))
				;Will Uncover Appropriate numbers
			
				((= 1 1)
				(print "Error In body of PlayTurnC"))
				
			);closes cond
		));closes let and conditional
	);closes cond
);closes defun

;Function Name: ExtractPlayable
;Purpose: Collect a list of numbers that can be played
;Parameters:
;		S -> Side
;		CD -> Cover Decision
;
;Return Value: list of playable numbers
;Algorithym:
;Check if cover decision is to cover (1) -> if so find *s and recurse with removed *
;Else, send to ExtractPlayableUncover
;Assistance Recieved: None
(defun ExtractPlayable (S CD) ;Side and CoverDec
	;(print S)
	(cond
		((= CD 1);if CoverDec is to Cover
		(cond
			( (eq (_Find S '*) '*)
			(ExtractPlayable (_Remove S '*) CD) )

			((= 1 1)
			S)

		));need to return a list of all the numbers in the list

		((= CD 0);if CoverDec is to Uncover
		(cond
			((= 1 1)
			(ExtractPlayableUncover S ()))
		));need to return a list of all the X's as their numbers in the list

	);closes cond

);closes defun

;Function Name: ExtractPlayableUncover
;Purpose: Collect a list of numbers that can be played
;Parameters:
;               S -> Side
;               Playable -> list of playable numbers 
;
;Return Value: list of playable numbers 
;Algorithym:
;Find a *, -> if so recurse with replacing that star and adding that star's value to playable
;Assistance Recieved: None
(defun ExtractPlayableUncover (S Playable);origional side and list to return

	;for debugging
	;(print S)
	;(print "above is S --------Below is Playable")
	;(print Playable)

	(cond
		((eq (_Find S '*) '*);will check if there is an X on the Side
		(ExtractPlayableUncover 
			(_ReplaceX S (_FindLoc S '* 1) 1) 
			(append Playable (cons (_FindLoc S '* 1) nil) )
		)
		);if so, recurse
		
		((= 1 1);
		Playable);else

	);closes cond
);closes defun






;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;HUMAN TURN CODE
;Function Name: SelectNumDice
;Purpose: allows player to choose the number of dice to roll
;Parameters:
;               P -> Player Side
;               
;
;Return Value: number of dice to roll 
;Algorithym: Send to StrategyNumDice
;Assistance Recieved: None
(defun SelectNumDice(P); PSide
	(StrategyNumDice P)
);closes defun

;Function Name: SelectCovDec
;Purpose: Allows player to select a cover decision
;Parameters:
;               R -> Roll
;		H -> Hside
;               C -> Cside
;Return Value: 1 for cover and 0 for uncover 
;Algorithym:
;Check if cover decision is forced, -> if so force it
;else allow the player to choose and ask for advice
;Assistance Recieved: None
(defun SelectCovDec(R H C);Roll Hside and Cside
	(let* (
		;variables
		(Forced (CheckForcedCovDec R H C))
	      )
		;body
		(cond	
			((equal Forced nil)		;Error Check
			(print "Error Forced = nil")
			2)

			((= Forced 2)	;no move is possible
			())
			
			((= Forced 1) ; must uncover
			1)

			((= Forced 0) ; must cover
                        0)
		
			((= 1 1)
			(print "Please Enter C to Cover, U to Uncover, or A for advice:")
			(ValidCovDec(read) R H C) )
	
		);closes cond
	);closes let
);closes defun

;Function Name: ValidCovDec
;Purpose: Function that will validate cover decision and give advice
;Parameters:
;               R -> Roll
;               H -> Hside
;               C -> Cside
;Return Value: a 1 for cover or 0 for uncover 
;Algorithym:
;Check if input eq C -> return 1
;Check if input eq U -> return 0
;Check if input eq A -> call computer Ai to get advice and recurse
;Assistance Recieved: None
(defun ValidCovDec(input R H C)
	(cond
		((eq input 'C)
		1)

		((eq input 'U)
		0)

		((eq input 'A);Will check for advice
		(print "The computer thinks that you should: ")

		(let* ( 
			;Variable
			(Advice (SelectCovDecC R C H))
				;uses SelectCovDecC for strategy but flips H and C
				;A bit of a confusing way to implement but it works well
		      )
			;Body of Let
			(cond
				((eq Advice 1)		;player is advised to cover
				(print 'Cover))
				((eq Advice 0)		;player is advised to uncover
				(print 'Uncover))
				((= 1 1)
				(print "Error in ValidCovDec")) ;else error
			);closes cond
		);closes let
		(print "Please enter either C or U or A")
		(ValidCovDec(read) R H C);Will recurse
		)

		((= 1 1)
		(print "Please enter either C or U or A")
		(ValidCovDec(read) R H C) )

	);closes cond
);close defun

;Function Name: SelectNumbersToPlay
;Purpose: Function will allow the human to select numbers to play
;Parameters:
;               R -> Roll
;               H -> Hside
;               C -> Cside
;		CD -> Cover Decision
;Return Value: a list of numbers to play
;Algorithym:
;Will Check Cover Decision and output a menu appropriately
;Will send to ReadNumbers to interpret
;if CD = 2, will return nil
;Assistance Recieved: None
(defun SelectNumbersToPlay(R H C CD);Roll and the Side of numbers that are being played
	(cond
		((eq CD 1);player has chosen to Cover
		(print "You have chosen to cover, Please enter individual numbers that you would like to cover")
		(print "You may enter 101 to restart your input")
		(print "You may enter 202 to end your turn")
		(print "You may enter 303 for advice")
		(ReadNumbers R (ExtractPlayable H 1) ())
		);closes conditional

		((eq CD 0);player has chosen to uncover
		(print "You have chosen to uncover, Please enter individual numbers that you would like to uncover")
		(print "You may enter 101 to restart your input")
                (print "You may enter 202 to end your turn")
                (print "You may enter 303 for advice")
		(ReadNumbers R (ExtractPlayable C 0) ())
		)

		((eq CD 2);Player cannot make any moves
		;(print "There are no moves to be made")
		nil);returns nil

	);closes cond	
);closes defun

;Function Name: ReadNumbers
;Purpose: Function will allow the human to select numbers to play
;Parameters:
;               R -> Roll
;               S -> Side
;               NumList -> list to hold numbers to play
;Return Value: a list of numbers to play
;Algorithym:
;Will read input and check for menu options
;101 resets input, 202 ends turn, 303 gives advice
;Validate input and if it is valid, add it to NumList and recurse
;If input is invalid, print why and recurse
;Assistance Recieved: None
(defun ReadNumbers (R S NumList);will need the Roll, Playable Numbers On Side, list to recurse
	(let* (
		;let Variables
		(input (read))
	      )
		;Let Body
		(cond
			((Not (typep input 'integer))		;Checks if input is a number
			(print "Please enter an integer: ")
			(ReadNumbers R S NumList)
			)

			((eq (AddAll NumList) R)		;if NumList adds up to roll
			NumList);Input is all read and so we return

			((eq input 101)				;will check for input restart
			(print "Input has been rest, you may continue to enter numbers.")
			(ReadNumbers R S ());will call ReadNumbers Again with an empty list
			)

			((eq input 202)				;will check for end turn
			());will return an empty list
	
			((eq input 303)				;will check for advice
			(print "The Computer thinks that you should play:")
			(print (GetNumToPlay R S))
			(print "You may now continue to enter numbers.")
			(ReadNumbers R S NumList)
			)

			((< input 1)				;checks if input is less than 1
			(print "Please enter a value greater than 1")
			(ReadNumbers R S NumList)
			)

			((> (+ (AddAll NumList) input) R)	;will Check if total exceeds roll
			(print "That number will make your total exceed your roll")
			(print "Please continue entering numbers.")
			(ReadNumbers R S NumList)
			)

			( (eq (_Find S input) nil )		;will check if the input is not playable
			(print "That Number is not playable.")
			(print "Please continue entering numbers")
			(ReadNumbers R S NumList)
			)

			((eq (_Find NumList input) input)	;Checks if number is already being played
			(print "This Number is already being played, please enter a different number")
			(ReadNumbers R S NumList)
			)

			((= 1 1)				;Else case, Number will be added to NumList
			(print "input accepted")
			(cond
				((eq (+ (AddAll NumList) input) R)                ;if NumList adds up to roll
	                        (return-from ReadNumbers (append (cons input nil) NumList) ));Input is all read and so we return
			)
			(ReadNumbers R S (append (cons input nil) NumList));should add element to list and recurse
			)

		);closes cond
	);closes let
);close defun for ReadNumbers

;Function Name: CheckForcedCovDec
;Purpose: Function will check if a cover decision is forced
;Parameters:
;               R -> Roll
;               P -> Player side
;               O -> Opponent side
;Return Value: 2 or 3 for no moves possible, 0 for uncover and 1 for cover
;Algorithym:
;Will Check if any move is possible -> if not, we return 2
;Will Check if cover is impossible -> if so, return 0
;Will Check if uncover is impossible -> if so, return 1
;Else return 3 and print error
;Assistance Recieved: None
(defun CheckForcedCovDec(R P O) ;will read in roll and board sides in terms of player's and opponents
	(cond
                ((= (CheckImpossible R P O) 1);check if making a move is impossible
                2);if so return 2

                ((= (CheckCoverImpossible R P) 1);check if covering is impossible
                0);if so return 0 for uncover

                ((= (CheckUncoverImpossible R O) 1);check if uncovering is impossible
		1);if so return 1 for cover

		((= 1 1);else
		;(print "Error in CheckForcedCovDec")
		3);return 3
        );cond should return a value telling us if a move is forced

);closes defun

;Function Name: CheckImpossible
;Purpose: Function will check if any move is possible
;Parameters:
;               R -> Roll
;               P -> Player side
;               O -> Opponent side
;Return Value: 1 if impossible and 0 if possible 
;Algorithym:
;Will Check if cover is impossible and uncover is impossible -> if so, return 1
;Else return 0
;Assistance Recieved: None
(defun CheckImpossible (R P O);Roll Player side Opponent Side
	(cond
		((= (CheckCoverImpossible R P) (CheckUncoverImpossible R O) 1);if impossible
		1);returns 1
		((= 1 1);else
		0);returns 0
	);closes cond

);closes defun

;Function Name: CheckCoverImpossible  
;Purpose: Function will check if covering is impossible      
;Parameters:
;               R -> Roll
;               P -> Player side
;               O -> Opponent side
;Return Value: 1 if impossible and 0 if possible 
;Algorithym:
;Will Check if the Ai thinks there is no numbers to possibly cover -> if so return 1
;Else return 0
;Assistance Recieved: None
(defun CheckCoverImpossible(R P);Roll, PSide
	(cond
		( (equal (GetNumToPlay R (ExtractPlayable P 1)) ());will check if it is impossible to cover 
		1) ; will return 1 if impossible
		
		((= 1 1)
		0);will return 0 if covering is possible

	);closes cond
);closes defun

;Function Name: CheckUncoverImpossible
;Purpose: Function will check if uncovering is impossible
;Parameters:
;               R -> Roll
;               P -> Player side
;               O -> Opponent side
;Return Value: 1 if impossible and 0 if possible
;Algorithym:
;Will Check if the Ai thinks there is no numbers to possibly uncover -> if so return 1
;Else return 0                
;Assistance Recieved: None
(defun CheckUncoverImpossible(R O) ;Roll, OSide
	(cond
		((equal (GetNumToPlay R (ExtractPlayable O 0)) ())
		1) ; will return 1 if uncover is impossible

		((= 1 1)
		0) ; will return 0 if uncover is possible

	);closes cond
);closes defun








;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;COMPUTER TURN CODE
;Function Name: SelectCoverDecC
;Purpose: Function will have the computer select a cover decision
;Parameters:
;               R -> Roll
;               H -> Human side
;               C -> Computer side
;Return Value: 1 for cover and 0 for uncover and 2 for no move possible
;Algorithym:
;Will Check if all moves are impossible -> if so return 2
;Will Check if Uncovering is impossible -> return 1
;Will Check if Covering is impossible -> return 0
;Will See if the sum of all numbers to cover is greater than the sum of all numbers to uncover -> return 0 (uncover)
;^Same but opposite -> the computer detects which way it is closer to victory
;If its a tie, then the computer goes decides which has less squares and chooses based off that
;else if is again a tie, it uncovers
;Assistance Recieved: None
(defun SelectCovDecC (R H C);Roll HSide and CSide
	;(print (AddAll (ExtractPlayable H 0)))
        ;(print (AddAll (ExtractPlayable C 1)))
	(cond
		((= 1 (CheckImpossible R C H) );Will Check if move is possible
		2) ;returns 2 to end turn
		
		((= 1 (CheckUncoverImpossible R H)) ;Will Check if Uncovering is impossinle, MUST COVER
		1)

		((= 1 (CheckCoverImpossible R C)) ;Will Check if Covering is impossible, MUST UNCOVER
		0)

;		((= 1 1)
;		(print (AddAll (ExtractPlayable H 0)))
;		(print (AddAll (ExtractPlayable C 1))) )

		((> (AddAll (ExtractPlayable H 0))(AddAll (ExtractPlayable C 1)))
		1)

		((< (AddAll (ExtractPlayable H 0))(AddAll (ExtractPlayable C 1)))
                0)

		((< (length (ExtractPlayable H 1)) (length (ExtractPlayable C 0)));will check if Hside has more numbers to play
		1) ;We want to prioritize cover
	
		((= 1 1);else
		0) ;We shall uncover 

	);close cond
);close defun

;Function Name: SelectNumbersToPlayC
;Purpose: Function will allow the computer select numbers to play
;Parameters:
;               R -> Roll
;               H -> Hside
;               C -> Cside
;               CD -> Cover Decision
;Return Value: a list of numbers to play
;Algorithym:
;if CD = 2 then will return nil
;Will Send to GetNumToPlay based off coverdecision and will pass the appropriate ExtractPlayable list
;Assistance Recieved: None
(defun SelectNumbersToPlayC (R H C CD);Roll, HSide, CSide, Coverdecision	
	(cond
		((eq CD 1);chose to cover
		(GetNumToPlay R (ExtractPlayable C 1)) );Will retreive best numbers to cover

		((eq CD 0);chose to uncover
		(GetNumToPlay R (ExtractPlayable H 0)) );Will retrieve best numbers to uncover

		((eq CD 2);No Move is playable
		nil);will return nil

		((= 1 1);else
		(print "Error In SelectNumbersToPlayC, Cover Decision not specified"))

	);closes cond

);closes defun






;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;STRATEGY CODE

;Function Name: StrategyNumDice
;Purpose: Function will determine the best number of dice to roll
;Parameters:
;               PSide -> Player's side
;
;
;Return Value: 1 or 2 for number of dice
;Algorithym:
;Will Check if PSide is empty -> if so return 1
;Will check if the first element in the list is eq '* -> recruse with rest of list
;Will check if the first element of the list is > 6 -> return 2
;else recurse with rest of PSide
;Assistance Recieved: None
(defun StrategyNumDice(PSide) ;Takes in the player's side
	(cond

		((equal PSide ())
		1)		

		((eq (first PSide) '*)
		(StrategyNumDice (rest PSide)))

		((> (first PSide) 6)
		2)

		((equal PSide ());
		1)

		((= 1 1);else
		(StrategyNumDice (rest PSide)) )
	)
);closes defun

;Function Name: StrategyNumbersToPlay
;Purpose: Function collect the best collection of numbers to play
;Parameters:
;               R -> Roll
;               PosNum -> list of possible numbers to play
;               count -> count holding the sum of all the numbers being considered for play
;               PosNum2 -> holds the origional list
;Return Value: a list of numbers to play + garbage, first values are good and last values are garbage
;Algorithym:
;Will Get the highest playable number and append it in a list to a recursive case where PosNum no longer has that number
;Will Check if that first number works with other numbers in the list to add up to roll
;If not, we will reset without that number (Start over from second highest number)
;If there was a case where the second recursive number caused the issue -> 2 3 4 6 R = 11 
;Then we remove the move recently added number from the list, same for if the third number caused the issue
;Assistance Recieved: None
(defun StrategyNumbersToPlay (R PosNum count PosNum2)	
	;(print "Got to StrategyNumbersToPlay")
	;(print PosNum)
	;(print count)
	;(print (GetHigh PosNum))
	(cond
		;Base Case
		((= R count)
		() );returns an empty list

		;Base Case 2
		((= (GetHigh PosNum) (- R count));check if roll-count = highest number in PosNum (should complete loop)
		(cons (GetHigh PosNum) nil))      ;will return number to play

		;Base Case 3
		((eq (GetHigh PosNum2) 0)
                 nil)

		;Recursive Case 1 -> Will Start whole loop over with PosNum2 getting rid of a number
                ((eq (GetHigh PosNum) 0)
                (cond
			;Checks if we cannot work with highest number
			((= count (GetHigh PosNum2))
			(StrategyNumbersToPlay
				R
				(_Remove PosNum2 (GetHigh PosNum2))
				0			
				(_Remove PosNum2 (GetHigh PosNum2))
			))

			;Checks if we cannot work with two highest numbers
			;will Check if count = highest + second highest in PosNum2
			;if so we will recurse as if we got rid of the second highest in PosNum2
			((= count (+ (GetHigh PosNum2) (GetHigh (_Remove PosNum2 (GetHigh PosNum2)))))
;For Debugging		(print "Cannot work with two highest numbers")
			(append (StrategyNumbersToPlay
                                R
                                (_Remove (_Remove PosNum2 (GetHigh PosNum2)) (GetHigh (_Remove PosNum2 (GetHigh PosNum2))) )
                                (GetHigh PosNum2)
                                PosNum2		;(_Remove PosNum2 (GetHigh PosNum2))
				)
				(cons (GetHigh PosNum2) nil)
			));closes append and conditional


			;Checks if we cannot work with three highest numbers
			((= count (+ 
					(GetHigh PosNum2) 
					(GetHigh (_Remove PosNum2 (GetHigh PosNum2)))
					(GetHigh (_Remove (_Remove PosNum2 (GetHigh PosNum2)) (GetHigh (_Remove PosNum2 (GetHigh PosNum2))))) 
				   );closes +
			 );closes =                            
;ForDebugging		(print "Cannot work with highest three numbers")
                        (append	(StrategyNumbersToPlay
                                        R						;Roll
				        (_Remove PosNum2 (GetThirdHigh PosNum2))	;PosNum2 - the third highest number
					(+ (GetHigh PosNum2) (GetSecondHigh PosNum2))	;Count = secondhigh + high
					PosNum2						;Origional PosNum2
					);closes StrategyNumbersTo Play Recursion

				(list (GetHigh PosNum2) (GetSecondHigh PosNum2));a list of the highest two numbers
                        ));closes append and conditional

			((= 1 1) ;else
;For Debugging		(print "Cannot Work with Highest Number")
			(StrategyNumbersToPlay
                                R
                                (_Remove PosNum2 (GetHigh PosNum2))
                                0
                                (_Remove PosNum2 (GetHigh PosNum2))
                        ));We'll just remove the highest number

		));closes cond and conditional for Recursion case 1

		;Recursive Case 2 ->will create a list of numbers to play
		((<= (+(GetHigh PosNum) count) R)
		(append 
			(StrategyNumbersToPlay 
				R						;Roll 
				(_Remove PosNum (GetHigh PosNum) )		;PosNum list minus number we want to play 
				(+ count (GetHigh PosNum) )			;count plus number we want to play
				PosNum2						;copy of origional PosNum
			) ;closes StrategyNumbersToPlay			
			(cons (GetHigh PosNum) nil)				;A list of the number we want to play

		)) ;closes append and recursive case
		;This whole block should make a list of numbers we want to play
		;This block will return the final list 

		;Recursive Case 3 -> will recurse without PosNum high
		((< R (+ (GetHigh PosNum) count))
		(StrategyNumbersToPlay 
			R 
			(_Remove PosNum (GetHigh PosNum)) 
			count 
			PosNum2
		))
									
		;Error Case 
		((= 1 1)
		(print "Error inside StrategyNumbersToPlay"))
	);closes cond

);closes defun


;Function Name: CheckStrategyNumbersToPlay
;Purpose: Function will check StrategyNumbersToPlay and get rid of garbage
;Parameters:
;               R -> Roll
;               l -> returned from StrategyNumbersToPlay
;
;Return Value: a list of numbers to play
;Algorithym:
;Will check if empty list was returned -> return nil
;Will check if the sum of the list is less then the roll -> return nil
;Will check if the sum of the list is = to roll -> return list
;Will get rid of the final number in the list and recruse
;Assistance Recieved: None
(defun CheckStrategyNumbersToPlay (R l) ;roll and returned list
	;(print l)
	(cond
		;Base Case 1
		((equal l nil)		;Will check if empty list returned
		nil)			; Will return nil for empty list

		;Base Case 2
		((< (AddAll l) R)	;Will Check if function could not reach Roll
		nil)			;Will return nil

		;Base Case 3
		((eq R (AddAll l))
		l)

		;Recursive Case 1
		((Not (eq (AddAll l) R)) ;Checks if all the numbers in the list dont add up to the roll
		(CheckStrategyNumbersToPlay R (_RemoveX l (- (length l) 1) 0)) )

		;Recursive Case 2
                ( (eq (first l) (_Find (rest l) (first l)) ) ;Checks for duplicates
                (CheckStrategyNumbersToPlay
                        R
                        (_RemoveX l (length (rest l)) 0)
                ))

		;Else trigger
		((= 1 1)
		l)
	);closes cond
);closes defun

;Function Name: GetNumToPlay
;Purpose: Function will collect the best numbers to play
;Parameters:
;               R -> Roll
;               PosNum -> list of playable numbers
;
;Return Value: a list of numbers to play
;Algorithym:
;Will collect a list from CheckStrategyNumbersToPlay
;Will check if there are any duplicate numbers -> if so return nil
;if not return the list
;Assistance Recieved: None
;Function will Combine StrategyNumbersToPlay and CheckStrategyNumbersToPlay in an easy to call function
(defun GetNumToPlay (R Posnum) ;roll and possible numbers to play
	(let* 
		;variables
		(
		 (l (CheckStrategyNumbersToPlay R (StrategyNumbersToPlay R Posnum 0 Posnum)));holds a list returned by AI
		)

		;body
		(cond
			((eq (first l) (_Find (rest l) (first l))) ;One FINAL Check that there are no repeating numbers
			nil)

			((= 1 1) ;else, list is Good to Go!
			l)
		)
	);closes let
);closes defun









;;Code Actually Runs



;;FUNCTION TESTING
(printWelcome) ; Simple output welcoming user
;(write (LoadSave)) ; Simple function that should read a response from the user as to whether or not to load a save
;(print (_Remove (GetHigh(CreateNewBoardSide(11))) 11 ))
;(print (Uncover(print (Cover( CreateNewBoardSide(ReadBoardSize)) 5) ) 5 ) ) ; will read board size and create a new board

;(print (CheckStrategyNumbersToPlay 12 (StrategyNumbersToPlay 12 (list 5 6 7 8 9) 0 (list 5 6 7 8 9) )))
;(print (_ReplaceX (list 1 2 3 4 '* 6 7 '* 9 10 11) (_FindLoc (list 1 2 3 4 '* 6 7 '* 9 10 11) '* 1) 1))
;(print (CoverFromList (CreateNewBoardSide 9) (list 2 5 6)))
;(print (UncoverFromList (list 1 '* '* '* '* '* '* '* 9) (list 2 5 6)))
;(print (ExtractPlayableUncover (list 1 2 3 4 '* 6 7 '* 9 10 11) () ) )
;(print (ExtractPlayable (list 1 2 3 4 5 '* 7 '* 9 10 11) 0))

;(DisplayBoard (_Remove (CreateNewBoardSide 9) 4 ) (GetHigh (list 1 8 10 11 8 10 11 3 4)) 1)
;(print (CalcHandicapNum 4))
;(print (CalcScore (list (list '* '* '* '* '* '* '* '* '*) (list 1 2 3 4 5 6 7 8 '*))))
;(print (GetNumToPlay 11 (ExtractPlayable (list '* 2 3 4 '* 6 '* '* '*) 1))) ;test highest two nums dont work
;(print (GetNumToPlay 9 (ExtractPlayable (list '* 2 '* '* '* '* 7 8 '*) 1))) ; test highest num doesnt work
;(print (GetNumToPlay 20 (ExtractPlayable (list '* 2 3 4 '* 6 '* '* 9) 1)));Tests highest three nums dont work
;(print (GetNumToPlay 12 (ExtractPlayable (list 1 2 3 4 5 6 7 8 9) 1)))
;(print (GetNumToPlay 12 (ExtractPlayable (list 1 2 '* 4 5 '* '* '* '*) 1)));tests getting four nums
;(print (GetNumToPlay 12 (ExtractPlayable (list 1 '* '* 4 5 6 7 8 9) 1)))
;(print (GetNumToPlay 11 (ExtractPlayable (list '* 2 '* 4 5 '* '* '* '*) 1)))
;(print (InterpretLoadSave (ReadSave 'LispSave.txt)))
;(print (get-file 'lispsave.txt))
;(print (GetThirdHigh (ExtractPlayable (list '* 2 3 4 '* 6 '* '* 9) 1)))


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;:TRUE MAIN CODE
(Begin(LoadSave))
