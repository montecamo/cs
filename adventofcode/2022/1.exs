output =
  File.stream!("1.input")
  |> Stream.map(fn x ->
    case x do
      "\n" -> x
      str -> String.replace(str, "\n", "") |> String.to_integer()
    end
  end)
  |> Enum.reduce(%{current: 0, max: 0}, fn calorie, %{current: current, max: max} ->
    case calorie do
      "\n" when current > max -> %{current: 0, max: current}
      "\n" -> %{current: 0, max: max}
      _ -> %{current: current + calorie, max: max}
    end
  end)

IO.puts(output.max)
