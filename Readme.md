# Train_DisplayRegisteredList

this app ha no final purpose, it is only here for me to practice and you to have an example if you need.

I am trying to read informations from a file and display those informations in QTreeWidge (which my final purpos, use, practice on QTreeWdiget). It will load a file and ask for the order of the headers. From that il will read the line and take the order from the modal to take as first level of the tree the first header in the list and so on.

The app has no design, d'ont need to when you only need to be practicle.

The app read from a tsv file for the moment ( branch fromCSV).
After taking which tsv header is to be inserted,
The app read each line and treat as a (sport?) competitor,
then it looks in the tree if the first selected entry exists, if not, it creates it.
After that it look at the childs in the tree and go to the next selected header and so on
until all the selected header are inserted in a tree.

this is tricky from tsv file, but funny enought to practice.

If you like you can use the Interface class Reader.h to create your own reader from (let's say) a json file, or Yaml file, or...

From Json I would expect something like, parsing objects, each ojbect contains some keys, the keys are what I call Headers here. each object has similar keys and the keys are insertd only once at the end your objects are sorted in the order you ask in the dialog. for example.

Enjoy if you need an example of how to use QTreeWidget.