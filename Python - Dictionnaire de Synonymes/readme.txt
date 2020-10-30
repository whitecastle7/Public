-
Project Name:						Synonym dictionnary


Programming Language:				Python (SQLite, NumPy)


How to run:							Run controller.py in command line
								with some of the following arguments
								--bd will (re)initilize the SQLite database.
								-e is for training, but also requires:
									-t followed by a number for the window
									--enc followed by the encoding type (utf-8)
									--chemin followed by the path to the text
								-r is for research, but also requires:
									-t followed by a number for the window


Notes:								There are a few (french) texts alongside the code for the program.
								It should be obvious that a research requires training first.

								Low RAM may prevent Python from building a large matrix
								if that happens simply use smaller texts or train one at a time.

								It is by no means a perfect way to find synonyms
								and some of the methods are less accurate then others.


The program:						While training, the program will run through the entire text
								and fill the database with potentiel synonyms.

								When in research mode, the program will ask for a word
								along with which calculation method (0, 1 or 2) to use
								and the number of potential synonyms.
								(10 synonyms and the third method (2) should give a good idea)


-