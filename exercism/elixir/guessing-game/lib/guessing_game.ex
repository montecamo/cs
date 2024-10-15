defmodule GuessingGame do
  def compare(_a, :no_guess) do
    "Make a guess"
  end

  def compare(secret, guess) when secret == guess do
    "Correct"
  end

  def compare(secret, guess) when abs(secret - guess) == 1 do
    "So close"
  end

  def compare(secret, guess) when secret < guess do
    "Too high"
  end

  def compare(secret, guess) when secret > guess do
    "Too low"
  end

  def compare(_a, _b) do
    "Make a guess"
  end

  def compare(_) do
    "Make a guess"
  end
end
