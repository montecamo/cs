map = %{
  "A" => :rock,
  "B" => :paper,
  "C" => :scissors,
  "X" => :rock,
  "Y" => :paper,
  "Z" => :scissors
}

item_value = %{rock: 1, paper: 2, scissors: 3}
result_value = %{lose: 0, draw: 3, win: 6}

rules = %{
  rock: %{
    rock: :draw,
    paper: :win,
    scissors: :lose
  },
  paper: %{
    rock: :lose,
    paper: :draw,
    scissors: :win
  },
  scissors: %{
    rock: :win,
    paper: :lose,
    scissors: :draw
  }
}

File.stream!("2.input")
|> Stream.map(&String.trim/1)
|> Stream.map(&String.split(&1, " "))
|> Stream.map(fn [a, b] -> [map[a], map[b]] end)
|> Stream.map(fn [a, b] ->
  result_value[rules[a][b]] + item_value[b]
end)
|> Enum.sum()
|> IO.puts()
