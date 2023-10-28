map = %{
  "A" => :rock,
  "B" => :paper,
  "C" => :scissors,
  "X" => :lose,
  "Y" => :draw,
  "Z" => :win
}

item_value = %{rock: 1, paper: 2, scissors: 3}
result_value = %{lose: 0, draw: 3, win: 6}

rules = %{
  rock: %{
    draw: :rock,
    win: :paper,
    lose: :scissors
  },
  paper: %{
    lose: :rock,
    draw: :paper,
    win: :scissors
  },
  scissors: %{
    win: :rock,
    lose: :paper,
    draw: :scissors
  }
}

File.stream!("2.input")
|> Stream.map(&String.trim/1)
|> Stream.map(&String.split(&1, " "))
|> Stream.map(fn [a, b] -> [map[a], map[b]] end)
|> Stream.map(fn [a, b] ->
  item_value[rules[a][b]] + result_value[b]
end)
|> Enum.sum()
|> IO.puts()
