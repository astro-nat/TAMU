
-- Assignment 2, CSCE-314
-- Section: 501
-- Student Name: Natalie Cluck
-- UIN: 723006213
-- Acknowledgements: Kyra Drake (Peer Teacher)

module Main where

import Test.HUnit
import System.Exit

factorial :: Int -> Int
factorial 1 = 1
factorial n = n * factorial (n-1)

fibonacci :: Int -> Int
fibonacci 0 = 0
fibonacci 1 = 1
fibonacci (n) = fibonacci(n-1) + fibonacci(n-2)

mySum :: [Int] -> Int
mySum [] = 0
mySum (x:xs) = x + mySum xs

flatten :: [[a]] -> [a]
flatten [] = []
flatten (a:rest) = a ++ flatten rest

myLength :: [a] -> Int
myLength [] = 0
myLength (x:xs) = 1 + myLength xs

isElement :: Eq a => a -> [a] -> Bool
isElement a [] = False
isElement a (x:xs)
	 | a == x = True
	 | otherwise = isElement a xs

type Set a = [a]

mkSet :: Eq a => [a] -> Set a
mkSet [] = []
mkSet (x:xs) = if isElement x xs then mkSet xs else (x:mkSet xs)

size ::  Set a -> Int
size [] = 0
size (x:xs) = 1 + myLength xs
	
subset :: Eq a => Set a -> Set a -> Bool 
subset [] b = True
subset (x:xs) b = if (isElement x b) then (subset xs b) else False
	
setEqual :: Eq a => Set a -> Set a -> Bool
setEqual a b = if (subset a b && subset b a) then True else False

powerset :: Set a -> Set (Set a)
powerset [] = [[]]
powerset (x:xs) = [[x] ++ y | y <- powerset xs] ++ powerset xs

myTestList = 
  TestList [ 
    "factorial" ~: factorial 3 ~=? 6
    
    , "fibonacci" ~: fibonacci 4 ~=? 3

    , "mySum" ~: mySum [1..10] ~=? 55
    
    , "flatten 1" ~: flatten [[]::[Int]] ~=? []
    , "flatten 2" ~: flatten [[]::[Int], [], []] ~=? []
    , "flatten 3" ~: flatten [[1], [2, 3, 4], [], [5, 6]] ~=? [1, 2, 3, 4, 5, 6]
      
    , "myLength" ~: myLength [1, 2, 3] ~=? 3
      
    , "isElement 1" ~: (isElement 'c' "abcd") ~=? True
    , "isElement 2" ~: (isElement 'e' "abcd") ~=? False
      
    , "mkSet 1" ~: size (mkSet "abcdaab") ~=? 4
    , "mkSet 2" ~: size (mkSet "abc") ~=? 3
      
    , "subset 1" ~: subset (mkSet "dbdb") (mkSet "abcdaab") ~=? True
    , "subset 2" ~: subset (mkSet "abc") (mkSet "bcccbhk") ~=? False
      
    , "setEqual 1" ~: setEqual (mkSet "abc") (mkSet "abcf") ~=? False
    , "setEqual 2" ~: setEqual (mkSet "abccbac") (mkSet "cbabc") ~=? True
      
    , "powerset 1" ~: size (powerset (mkSet []::[Int])) ~=? 1
    , "powerset 2" ~: size (powerset (mkSet [1])) ~=? 2
    , "powerset 3" ~: size (powerset (mkSet [1, 2])) ~=? 4
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
