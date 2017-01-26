
-- Assignment 3, CSCE-314
-- Section: 501
-- Student Name: Natalie Cluck
-- UIN: 723006213
-- Acknowledgements: Kyra Drake (Peer Teacher)

module Main where

import Test.HUnit
import System.Exit
import Data.List
import Data.Char

triads :: Int -> [(Int, Int, Int)]
triads n = [ (a,b,c) | a <- [1..n], b <- [1..n], c <- [1..n], (a^2)+(b^2)==(c^2), a < b ]

perfect :: [Int]
perfect = [ x | x <- [1..100000], x == sum([ i | i <- [1..x], x `mod` i == 0, x /= i]) ]

mergeBy :: (a -> a -> Bool) -> [a] -> [a] -> [a]
mergeBy pred xs [] = xs
mergeBy pred [] ys         = ys
mergeBy pred (x:xs) (y:ys)
    | pred x y = x: mergeBy pred xs (y:ys)
    | otherwise = y: mergeBy pred (x:xs) ys

split :: [a] -> ([a],[a])   
split (x:y:zs) = (x:xs,y:ys) where (xs,ys) = split zs
split xs       = (xs,[]) 

mergeSortBy :: (a -> a -> Bool) -> [a] -> [a]
mergeSortBy p [] = []
mergeSortBy p [x] = [x]
mergeSortBy p x = mergeBy p (mergeSortBy p x1) (mergeSortBy p x2)
	where
		(x1,x2) = split x

mergeSort :: Ord a => [a] -> [a]
mergeSort [] = []
mergeSort [x] = [x]
mergeSort x = mergeSortBy (<) x

multiply :: [Int] -> Int
multiply x = foldr (*) 1 x

concatenate :: [String] -> String
concatenate x = foldl (++) "" x

concatenateAndUpcaseOddLengthStrings :: [String] -> String
concatenateAndUpcaseOddLengthStrings [] = " "
concatenateAndUpcaseOddLengthStrings x = map toUpper (concatenate (filter (\x -> length x `mod` 2 /= 0) x))

-- helper function for insertionSort
insertion :: Ord a => a -> [a] -> [a]
insertion x [] = [x]
insertion x (s:ss) = if x < s then x : s : ss else s : insert x ss

insertionSort :: Ord a => [a] -> [a]
insertionSort = foldr insertion []

maxElementOfAList :: Ord a => [a] -> a 
maxElementOfAList x = foldl1 max x

keepInBetween :: Int -> Int -> [Int] -> [Int]
keepInBetween a b x = filter (\x -> (x >= a)&&(x <= b)) x

data Tree a b = Branch b (Tree a b) (Tree a b)
              | Leaf a

preorder  :: (a -> c) -> (b -> c) -> Tree a b -> [c]
postorder :: (a -> c) -> (b -> c) -> Tree a b -> [c]
inorder   :: (a -> c) -> (b -> c) -> Tree a b -> [c]

preorder f g (Leaf a) = [f a]
preorder f g (Branch b left right) = [g b] ++ preorder f g left ++ preorder f g right

postorder f g (Leaf a) = [f a]
postorder f g (Branch b left right) = postorder f g left ++ postorder f g right ++ [g b]

inorder f g (Leaf a) = [f a]
inorder f g (Branch b left right) = inorder f g left ++ [g b] ++ inorder f g right

data E = IntLit Int
       | BoolLit Bool
       | Plus E E
       | Minus E E
       | Multiplies E E
       | Divides E E
       | Equals E E
         deriving (Eq, Show)

		 
-- helper function for eval		 
toInt :: E -> Int
toInt (IntLit x) = x
		 
eval :: E -> E
eval (IntLit x) = IntLit x
eval (Plus a1 a2) = IntLit $ (toInt $ eval a1) + (toInt $ eval a2)
eval (Equals a1 a2) = BoolLit $ (toInt $ eval a1) == (toInt $ eval a2)
eval (Minus a1 a2) = IntLit $ (toInt $ eval a1) - (toInt $ eval a2)
eval (Multiplies a1 a2) = IntLit $ (toInt $ eval a1) * (toInt $ eval a2)
eval (Divides a1 a2) = IntLit $ (toInt $ eval a1) `div` (toInt $ eval a2) 

mytree = Branch "A" 
           (Branch "B" 
              (Leaf 1) 
              (Leaf 2)) 
           (Leaf 3)

instance (Show a, Show b) => Show (Tree a b) 
	where 
		show t = showIndent " " t where
				showIndent indent (Leaf a) = indent ++ (show a) ++ "\n"
				showIndent indent (Branch b t1 t2) = indent ++ show b ++ "\n" ++ showIndent (' ':indent) t1 ++ showIndent (' ':indent) (t2)

program = Equals 
            (Plus (IntLit 1) (IntLit 2))
            (Minus
             (IntLit 5)
             (Minus (IntLit 3) (IntLit 1)))
    
myTestList =

  let te s e a = test $ assertEqual s e a
      tb s b = test $ assertBool s b

  in
    TestList [ 
        tb "triads 1" $ [(3, 4, 5)] == triads 5
      , tb "triads 2" $ [(3, 4, 5), (6, 8, 10)] == ( sort $ triads 10)

      , tb "perfect" $ take 3 perfect == [6, 28, 496]
        
      , te "mergeSort 1" " adhllowy" (mergeSort "howdy all") 
      , te "mergeSort 2" "" (mergeSort "") 
      , te "mergeSort 3" "x" (mergeSort "x") 
        
      , te "mergeSortBy 1" " 'eggim" (mergeSortBy (<) "gig 'em") 
      , te "mergeSortBy 2" "nmlkieecbbaJ  " (mergeSortBy (>) "Jack be nimble")
      , te "mergeSortBy 3" "" (mergeSortBy (<) "")

      , te "multiply" 10 (multiply [-2, -1, 5])
      , te "concatenate" "ABCD" (concatenate ["AB", "", "", "C", "D", ""])

      , te "concatenateAndUpcaseOddLengthStrings"
          "HERE'S AN EXAMPLE" (concatenateAndUpcaseOddLengthStrings ["here's ", "an ", "a ", "example"])

      , te "insertionSort" "  Jabcceikkqu" (insertionSort "Jack be quick")
      , te "max in a list" 100 (maxElementOfAList [3, 100, 0])
      , te "keepInBetween" [3,0,20,2] (keepInBetween 0 20 [77, 3, -1, 0, 21, 20, -9, 2])

      , te "preorder" "AB123" (concatenate (preorder show id mytree))
      , te "postrder" "12B3A" (concatenate (postorder show id mytree))
      , te "inorder" "1B2A3" (concatenate (inorder show id mytree))

      , te "eval" (BoolLit True) (eval program)
      ]

main = do c <- runTestTT myTestList
          putStrLn $ show c
          let errs = errors c
              fails = failures c
          exitWith (codeGet errs fails)
          
codeGet errs fails
 | fails > 0       = ExitFailure 2
 | errs > 0        = ExitFailure 1
 | otherwise       = ExitSuccess
