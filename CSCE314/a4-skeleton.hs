
-- Assignment 4, CSCE-314
-- Section: 501
-- Student Name: Natalie Cluck
-- UIN: 723006213
-- 

module Main where

import Prelude hiding (lookup)

import Test.HUnit
import System.Exit

-- some useful helper functions
lookup s [] = Nothing
lookup s ((k,v):xs) | s == k = Just v
        | otherwise = lookup s xs

asInt (VInt v) = v
asInt x = error $ "Expected a number, got " ++ show x

asBool (VBool v) = v
asBool x = error $ "Expected a boolean, got " ++ show x

fromJust (Just v) = v
fromJust Nothing = error "Expected a value in Maybe, but got Nothing"


-- AST definition for W
data WValue = VInt Int 
            | VBool Bool 
              deriving (Eq, Show)

data WExp = Val WValue
          | Var String

          | Plus WExp WExp
          | Minus WExp WExp
          | Multiplies WExp WExp
          | Divides WExp WExp

          | Equals WExp WExp
          | NotEqual WExp WExp
          | Less WExp WExp
          | Greater WExp WExp
          | LessOrEqual WExp WExp
          | GreaterOrEqual WExp WExp

          | And WExp WExp
          | Or WExp WExp
          | Not WExp

data WStmt = Empty
           | VarDecl String WExp
           | Assign String WExp
           | If WExp WStmt WStmt
           | While WExp WStmt
           | Block [WStmt]

type Memory = [(String, WValue)]
marker = ("|", undefined)
isMarker (x, _) = x == "|"

toInt :: WValue -> Int
toInt (VInt x) = x

toBool :: WValue -> Bool
toBool (VBool True) = True
toBool (VBool False) = False

-- eval function
eval :: WExp -> Memory -> WValue
eval (Val x) _ = x
eval (Var str) mem = fromJust (lookup str mem)
eval (Plus a1 a2) mem = VInt $ (toInt $ eval a1 mem) + (toInt $ eval a2 mem)
eval (Minus a1 a2) mem = VInt $ (toInt $ eval a1 mem) - (toInt $ eval a2 mem)
eval (Multiplies a1 a2) mem = VInt $ (toInt $ eval a1 mem) * (toInt $ eval a2 mem)
eval (Divides a1 a2) mem = VInt $ (toInt $ eval a1 mem) `div` (toInt $ eval a2 mem)
eval (Equals a1 a2) mem = VBool $ (toInt $ eval a1 mem) == (toInt $ eval a2 mem)
eval (NotEqual a1 a2) mem = VBool $ (toInt $ eval a1 mem) /= (toInt $ eval a2 mem)
eval (Less a1 a2) mem = VBool $ (toInt $ eval a1 mem) < (toInt $ eval a2 mem)
eval (Greater a1 a2) mem = VBool $ (toInt $ eval a1 mem) > (toInt $ eval a2 mem)
eval (LessOrEqual a1 a2) mem = VBool $ (toInt $ eval a1 mem) <= (toInt $ eval a2 mem)
eval (GreaterOrEqual a1 a2) mem = VBool $ (toInt $ eval a1 mem) >= (toInt $ eval a2 mem)
eval (And a1 a2) mem = VBool $ (toBool $ eval a1 mem) && (toBool $ eval a2 mem)
eval (Or a1 a2) mem = VBool $ (toBool $ eval a1 mem) || (toBool $ eval a2 mem)
eval (Not a1) mem = VBool $ not (toBool $ eval a1 mem)



-- exec function
exec :: WStmt -> Memory -> Memory
exec (Empty) mem = mem
exec (VarDecl str exp) mem = (++) [(str,(eval exp mem))] mem
exec (Assign str exp) mem = (++) [(str,(eval exp mem))] mem
exec (If exp stm1 stm2) mem =
    exec (if eval exp mem == VBool True then stm1 else stm2) mem
exec (While exp stm) mem =
    if eval exp mem == VBool True
        then do
            exec (While exp stm) (exec stm mem)
    else mem
exec (Block _) mem = (++) [marker] mem


-- example programs
prog1 = Block
     [
       VarDecl "x" (Val (VInt 0)),
       VarDecl "b" (Greater (Var "x") (Val (VInt 0))),
       If (Or (Var "b") (Not (GreaterOrEqual (Var "x") (Val (VInt 0)))))
         ( Block [ Assign "x" (Val (VInt 1)) ] )
         ( Block [ Assign "x" (Val (VInt 2)) ] )
     ]

factorial =
  Block
  [
    VarDecl "acc" (Val (VInt 1)),
    While (Greater (Var "arg") (Val (VInt 1)))
    (
      Block
      [
        Assign "acc" (Multiplies (Var "acc") (Var "arg")),
        Assign "arg" (Minus (Var "arg") (Val (VInt 1)))         
      ]
    ),
    Assign "result" (Var "acc")
  ]


-- unit tests
myTestList =

    let te s e a = test $ assertEqual s e a
        tb s b = test $ assertBool s b

    in

    TestList [

    test $ assertEqual "prog1 test" [] (exec prog1 []),
    test $ assertEqual "Plus test" (VInt 3) (eval (Plus (Val (VInt 1)) (Val (VInt 2))) []),
    test $ assertEqual "Minus and Plus test" (VInt 5) (eval (Plus (Minus (Val (VInt 10)) (Val (VInt 1))) (Val (VInt (-4)))) []),
    test $ assertEqual "Multiply test " (VInt 9) (eval (Multiplies (Val (VInt 3)) (Val (VInt 3))) []),
    test $ assertEqual "Divide" (VInt 5) (eval (Divides (Val (VInt 15)) (Val (VInt 3))) []),
    test $ assertEqual "Multiply and Divide" (VInt 25) (eval (Multiplies (Divides (Val (VInt 15)) (Val (VInt 3))) (Divides (Val (VInt 20)) (Val (VInt 4))))  []),
    test $ assertEqual "Add and Multiply" (eval (Multiplies (Plus (Val (VInt 3)) (Val (VInt 4))) (Plus (Val (VInt 100)) (Val (VInt 200)))) []) (VInt 2100),
    test $ assertEqual "NotEqual" (VBool False) (eval (NotEqual (Val (VInt 3)) (Val (VInt 3))) []),
    test $ assertEqual "Equal" (VBool True) (eval (Equals (Plus (Val (VInt 3)) (Val (VInt 3))) (Minus (Val (VInt 10)) (Val (VInt 4)))) []),
    test $ assertEqual "Less" (VBool True) (eval (Less (Plus (Val (VInt 3)) (Val (VInt 3))) (Minus (Val (VInt 20)) (Val (VInt 4)))) []),
    test $ assertEqual "Greater" (VBool False) (eval (Greater (Plus (Val (VInt 3)) (Val (VInt 3))) (Minus (Val (VInt 20)) (Val (VInt 4)))) []),
    test $ assertEqual "GreaterOrEqual" (VBool False) (eval (GreaterOrEqual (Plus (Val (VInt 3)) (Val (VInt 3))) (Minus (Val (VInt 20)) (Val (VInt 4)))) []),
    test $ assertEqual "LessOrEqual" (VBool True) (eval (LessOrEqual (Plus (Val (VInt 3)) (Val (VInt 3))) (Minus (Val (VInt 20)) (Val (VInt 4)))) []),
    test $ assertEqual "EqualOrGreater" (VBool True) (eval (GreaterOrEqual (Plus (Val (VInt 3)) (Val (VInt 4))) (Minus (Val (VInt 1)) (Val (VInt 0)))) []),
    test $ assertEqual "Divide and Minus" (VInt 510) (eval (Minus (Divides (Val (VInt 1040)) (Val (VInt 2))) (Divides (Val (VInt 100)) (Val (VInt 10)))) []),
    test $ assertEqual "Add Several" (VInt 500) (eval (Plus (Val (VInt 100)) (Plus (Val (VInt 100)) (Plus (Val (VInt 100)) (Plus (Val (VInt 100)) (Val (VInt 100)))))) [] ),

    let res = lookup "result" (exec factorial [("result", VInt (-1)), ("arg", VInt 10)])
    in test $ assertBool "factorial of 10" (3628800 == asInt (fromJust res))
    ]    

-- main: run the unit tests  
main = do c <- runTestTT myTestList
          putStrLn $ show c
          let errs = errors c
              fails = failures c
          if (errs + fails /= 0) then exitFailure else return ()

