defmodule FreelancerRates do
  def daily_rate(hourly_rate) do
    hourly_rate * 8 * 1.0
  end

  def apply_discount(before_discount, discount) do
    before_discount * (100 - discount) / 100
  end

  def monthly_rate(hourly_rate, discount) do
    FreelancerRates.apply_discount(hourly_rate, discount)
    |> FreelancerRates.daily_rate()
    |> (&(&1 * 22)).()
    |> Float.ceil()
    |> trunc()
  end

  def days_in_budget(budget, hourly_rate, discount) do
    FreelancerRates.apply_discount(hourly_rate, discount)
    |> FreelancerRates.daily_rate()
    |> (&(budget / &1)).()
    |> Float.floor(1)
  end
end
