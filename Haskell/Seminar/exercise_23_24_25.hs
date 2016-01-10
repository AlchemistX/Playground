main = do
        contents <- readFile "triangle1.txt"
        let triangle = map (map (\x -> read x::Int)).map words.lines $ contents
        print $ maxPath triangle

-- 23
maxPath::[[Int]] -> Int
maxPath triangle = head $ foldr1 f triangle
                    -- f:: [Int] -> [Int] -> [Int]
                    where f as bs = zipWith (+) as $ zipWith max bs (tail bs)

