defmodule TakeANumber do
  def loop(count \\ 0) do
    receive do
      {:report_state, pid} ->
        send(pid, count)
        loop(count)

      {:take_a_number, pid} ->
        send(pid, count + 1)
        loop(count + 1)

      :stop ->
        nil

      _ ->
        loop(count)
    end
  end

  def start() do
    spawn(&TakeANumber.loop/0)
  end
end
