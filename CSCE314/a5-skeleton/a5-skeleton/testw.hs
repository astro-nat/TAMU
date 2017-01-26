module Main where

import Test.HUnit
import W
import WParser

-- unit tests
myTestList =

    let te s e a = test $ assertEqual s e a
        tb s b = test $ assertBool s b

    in

	TestList [

       	test $ assertEqual "test1" (VInt 40) (run test1.w) [],
        test $ assertEqual "test2" (VInt 9) (run test2.w) [],
        test $ assertEqual "test3" (VInt 4) (run test3.w) [],
        test $ assertEqual "test4" (VInt 4) (run test4.w) [],
        test $ assertEqual "test5" (VInt 3) (run test5.w) []

	test(multimod001, normal, multipod_compile_and_run, ["test1","test2","test3","test4","test5"])
        ]

-- main: run the unit tests
main = do c <- runTestTT myTestList
	  putStrLn $ show c
	  let errs = errors c
	      fails = failures c
	  if (errs + fails /= 0) then exitFailure else return ()
