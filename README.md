# File Search Engine

This program implements a mini search engine on a file directory of the user's choice in C. It works by indexing all the words in the files in a directory and then provides the user with the ability to make a one-word query. When a word is queried on the command line, a list of documents including it is shown. "Stop-Words" like "the, and, but, a", etc will be omitted from the search query. 

## Getting Started (How to Run)

Copy this repository and run the makefile on a command line. Then to execute do

```
FileSearch <stop word list file> <documents to be searched>
```

## Authors

* **Shayla Moore** - *Initial work*

## Acknowledgments

*Inspiration goes to this being a project for my CS302 class which is Data Structures and Algorithms II
