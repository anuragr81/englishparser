

import pyparsing as pyp

def listnouns() : 
 #res = pyp.Literal("anurag")    \
 #       | pyp.Literal("habib")  \
 #       | pyp.Literal("champion")  \
 #       | pyp.Literal("captor") 
 #print res
 nouns = ('anurag','captor','champion')
 for i,n in enumerate(nouns):
     if i == 0: 
         res = pyp.Literal(n)
     else:
         res = res | pyp.Literal(n)

 return res

