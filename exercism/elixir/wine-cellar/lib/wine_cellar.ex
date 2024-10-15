defmodule WineCellar do
  def explain_colors do
    [
      white: "Fermented without skin contact.",
      red: "Fermented with skin contact using dark-colored grapes.",
      rose: "Fermented with some skin contact, but not enough to qualify as a red wine."
    ]
  end

  def filter(cellar, color, opts \\ []) do
    cellar
    |> Keyword.filter(fn {key, _} -> key == color end)
    |> Keyword.values()
    |> Enum.filter(fn {_, year, _} ->
      if Keyword.has_key?(opts, :year), do: year == opts[:year], else: true
    end)
    |> Enum.filter(fn {_, _, country} ->
      if Keyword.has_key?(opts, :country), do: country == opts[:country], else: true
    end)
  end
end
