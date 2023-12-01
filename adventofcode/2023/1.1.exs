defmodule Parser do
  defp parse(str) do
    [_, first | _] = Regex.run(~r/(\d)/, str)
    [_, second | _] = Regex.run(~r/.*(\d)/, str)

    "#{first}#{second}"
  end

  def main() do
    File.stream!("input")
    |> Stream.map(&parse/1)
    |> Stream.map(&String.to_integer/1)
    |> Enum.sum()
  end
end

IO.inspect(Parser.main())
