defmodule Parser do
  @number ~S"(\d|one|two|three|four|five|six|seven|eight|nine)"

  defp to_number("one"), do: "1"
  defp to_number("two"), do: "2"
  defp to_number("three"), do: "3"
  defp to_number("four"), do: "4"
  defp to_number("five"), do: "5"
  defp to_number("six"), do: "6"
  defp to_number("seven"), do: "7"
  defp to_number("eight"), do: "8"
  defp to_number("nine"), do: "9"
  defp to_number(num), do: num

  defp parse_number(str, regex) do
    Regex.compile!(regex) |> Regex.run(str) |> Enum.at(1) |> to_number()
  end

  defp parse(str) do
    first = parse_number(str, "#{@number}")
    second = parse_number(str, ".*#{@number}")

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
