data Shape = Circle Float | Rectangle Float

name :: Shape -> String
name (Circle _) = "Circle shape"
name (Rectangle _) = "Rectangle shape"

main = putStrLn (name (Circle 1))
