-
Synonym dictionnary
Python (SQLite, NumPy)
This code/program can be run easily and should work without problems.

This small program has a few fonctions.
Firstly, it is run by command line and takes in a few arguments.
--bd will (re)initilize the SQLite database.
-e is for training, but also requires:
	-t followed by a number for the window
	--enc followed by the encoding type (utf-8)
	--chemin followed by the path to the text
-r is for research, but also requires:
	-t followed by a number for the window
	
There are a few (french) texts alongside the code for the program.
It should be obvious that a research requires training first.

While training, the program will run through the entire text
and fill the database with potentiel synonyms.

When in research mode, the program will ask for a word
along with which calculation method to use
and the number of potential synonyms.

It is by no means a perfect way to find synonyms
and some of the methods are less accurate then others.

-