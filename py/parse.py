

import sys
from nouns import listnouns

import pyparsing as pyp
# Example : 
#  greet = pyp.Word (pyp.alphas) + ","+ pyp.Word (pyp.alphas)
#  print greet.parseString(sys.argv[1])

def purify(noun):
    return noun

word = pyp.Word(pyp.alphas)
noun = word
verb = word


sentence = ( listnouns() )  +verb+noun
##sentence = (  pyp.Literal("anurag") | pyp.Literal("kaka") )  +verb+noun


print "The processing is case-InsenSitiVe" 

print sentence.parseString(str(sys.argv[1]).lower())

