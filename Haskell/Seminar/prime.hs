isPrime n = [1, n] == [d | d <- [1..n], n `mod` d == 0]

prime = filter isPrime [1..]

sieve (p:xs) = [x | x <- xs, x `mod` p /= 0]
prime_sieve = map head $ iterate sieve [2..] 
