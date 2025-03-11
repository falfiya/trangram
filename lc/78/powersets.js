subsets=n=>[...Array(2**n.length)].map((_,p)=>n.filter((_,i)=>+[...p.toString(2)].reverse()[i]))
