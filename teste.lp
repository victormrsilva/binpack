\ LP format - for model browsing. Use MPS format to capture full model detail.
Minimize
  y(2) + y(4) + y(1) + y(24)
Subject To
 capacidade(j=2): - 7 y(2) + 2 x(2,2) + 2 x(4,2) + 3 x(7,2) + 3 x(1,2)
   + 3 x(3,2) + 3 x(5,2) + 4 x(6,2) <= 0
 capacidade(j=4): - 7 y(4) + 2 x(2,4) + 2 x(4,4) + 3 x(7,4) + 3 x(1,4)
   + 3 x(3,4) + 3 x(5,4) + 4 x(6,4) <= 0
 capacidade(j=1): - 7 y(1) + 2 x(2,1) + 2 x(4,1) + 3 x(7,1) + 3 x(1,1)
   + 3 x(3,1) + 3 x(5,1) + 4 x(6,1) <= 0
 capacidade(j=24): - 7 y(24) + 2 x(2,24) + 2 x(4,24) + 3 x(7,24)
   + 3 x(1,24) + 3 x(3,24) + 3 x(5,24) + 4 x(6,24) <= 0
 unico(i=2): x(2,2) + x(2,4) + x(2,1) + x(2,24) = 1
 unico(i=4): x(4,2) + x(4,4) + x(4,1) + x(4,24) = 1
 unico(i=7): x(7,2) + x(7,4) + x(7,1) + x(7,24) = 1
 unico(i=1): x(1,2) + x(1,4) + x(1,1) + x(1,24) = 1
 unico(i=3): x(3,2) + x(3,4) + x(3,1) + x(3,24) = 1
 unico(i=5): x(5,2) + x(5,4) + x(5,1) + x(5,24) = 1
 unico(i=6): x(6,2) + x(6,4) + x(6,1) + x(6,24) = 1
 conflito(i=2,j=1,k=2): x(2,2) + x(1,2) <= 1
 conflito(i=2,j=1,k=4): x(2,4) + x(1,4) <= 1
 conflito(i=2,j=1,k=1): x(2,1) + x(1,1) <= 1
 conflito(i=2,j=1,k=24): x(2,24) + x(1,24) <= 1
 conflito(i=2,j=5,k=2): x(2,2) + x(5,2) <= 1
 conflito(i=2,j=5,k=4): x(2,4) + x(5,4) <= 1
 conflito(i=2,j=5,k=1): x(2,1) + x(5,1) <= 1
 conflito(i=2,j=5,k=24): x(2,24) + x(5,24) <= 1
 conflito(i=4,j=3,k=2): x(4,2) + x(3,2) <= 1
 conflito(i=4,j=3,k=4): x(4,4) + x(3,4) <= 1
 conflito(i=4,j=3,k=1): x(4,1) + x(3,1) <= 1
 conflito(i=4,j=3,k=24): x(4,24) + x(3,24) <= 1
 conflito(i=4,j=6,k=2): x(4,2) + x(6,2) <= 1
 conflito(i=4,j=6,k=4): x(4,4) + x(6,4) <= 1
 conflito(i=4,j=6,k=1): x(4,1) + x(6,1) <= 1
 conflito(i=4,j=6,k=24): x(4,24) + x(6,24) <= 1
 conflito(i=7,j=5,k=2): x(7,2) + x(5,2) <= 1
 conflito(i=7,j=5,k=4): x(7,4) + x(5,4) <= 1
 conflito(i=7,j=5,k=1): x(7,1) + x(5,1) <= 1
 conflito(i=7,j=5,k=24): x(7,24) + x(5,24) <= 1
 conflito(i=7,j=6,k=2): x(7,2) + x(6,2) <= 1
 conflito(i=7,j=6,k=4): x(7,4) + x(6,4) <= 1
 conflito(i=7,j=6,k=1): x(7,1) + x(6,1) <= 1
 conflito(i=7,j=6,k=24): x(7,24) + x(6,24) <= 1
 conflito(i=1,j=2,k=2): x(2,2) + x(1,2) <= 1
 conflito(i=1,j=2,k=4): x(2,4) + x(1,4) <= 1
 conflito(i=1,j=2,k=1): x(2,1) + x(1,1) <= 1
 conflito(i=1,j=2,k=24): x(2,24) + x(1,24) <= 1
 conflito(i=3,j=4,k=2): x(4,2) + x(3,2) <= 1
 conflito(i=3,j=4,k=4): x(4,4) + x(3,4) <= 1
 conflito(i=3,j=4,k=1): x(4,1) + x(3,1) <= 1
 conflito(i=3,j=4,k=24): x(4,24) + x(3,24) <= 1
 conflito(i=3,j=5,k=2): x(3,2) + x(5,2) <= 1
 conflito(i=3,j=5,k=4): x(3,4) + x(5,4) <= 1
 conflito(i=3,j=5,k=1): x(3,1) + x(5,1) <= 1
 conflito(i=3,j=5,k=24): x(3,24) + x(5,24) <= 1
 conflito(i=5,j=2,k=2): x(2,2) + x(5,2) <= 1
 conflito(i=5,j=2,k=4): x(2,4) + x(5,4) <= 1
 conflito(i=5,j=2,k=1): x(2,1) + x(5,1) <= 1
 conflito(i=5,j=2,k=24): x(2,24) + x(5,24) <= 1
 conflito(i=5,j=7,k=2): x(7,2) + x(5,2) <= 1
 conflito(i=5,j=7,k=4): x(7,4) + x(5,4) <= 1
 conflito(i=5,j=7,k=1): x(7,1) + x(5,1) <= 1
 conflito(i=5,j=7,k=24): x(7,24) + x(5,24) <= 1
 conflito(i=5,j=3,k=2): x(3,2) + x(5,2) <= 1
 conflito(i=5,j=3,k=4): x(3,4) + x(5,4) <= 1
 conflito(i=5,j=3,k=1): x(3,1) + x(5,1) <= 1
 conflito(i=5,j=3,k=24): x(3,24) + x(5,24) <= 1
 conflito(i=6,j=4,k=2): x(4,2) + x(6,2) <= 1
 conflito(i=6,j=4,k=4): x(4,4) + x(6,4) <= 1
 conflito(i=6,j=4,k=1): x(4,1) + x(6,1) <= 1
 conflito(i=6,j=4,k=24): x(4,24) + x(6,24) <= 1
 conflito(i=6,j=7,k=2): x(7,2) + x(6,2) <= 1
 conflito(i=6,j=7,k=4): x(7,4) + x(6,4) <= 1
 conflito(i=6,j=7,k=1): x(7,1) + x(6,1) <= 1
 conflito(i=6,j=7,k=24): x(7,24) + x(6,24) <= 1
Bounds
Binaries
 y(2) x(2,2) x(4,2) x(7,2) x(1,2) x(3,2) x(5,2) x(6,2) y(4) x(2,4) x(4,4)
 x(7,4) x(1,4) x(3,4) x(5,4) x(6,4) y(1) x(2,1) x(4,1) x(7,1) x(1,1) x(3,1)
 x(5,1) x(6,1) y(24) x(2,24) x(4,24) x(7,24) x(1,24) x(3,24) x(5,24)
 x(6,24)
End
