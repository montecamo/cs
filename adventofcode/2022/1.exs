File.stream!("1.input")
|> Stream.map(&String.replace(&1, "\n", ""))
|> Stream.map(fn x ->
  case x do
    "" -> 0
    str -> String.to_integer(str)
  end
end)
|> Stream.chunk_by(&(&1 == 0))
|> Stream.map(&Enum.sum(&1))
|> Enum.sort()
|> Enum.take(-3)
|> Enum.sum()
|> IO.puts()
