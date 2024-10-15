defmodule Lasagna do
  def expected_minutes_in_oven(), do: 40

  def remaining_minutes_in_oven(elapsed), do: Lasagna.expected_minutes_in_oven() - elapsed

  def preparation_time_in_minutes(layers), do: layers * 2

  def total_time_in_minutes(layers, elapsed),
    do: Lasagna.preparation_time_in_minutes(layers) + elapsed

  def alarm(), do: "Ding!"
end
