defmodule LogLevel do
  def to_label(level, legacy?) do
    case level do
      0 when not legacy? -> :trace
      1 -> :debug
      2 -> :info
      3 -> :warning
      4 -> :error
      5 when not legacy? -> :fatal
      _ -> :unknown
    end
  end

  def alert_recipient(level, legacy?) do
    case to_label(level, legacy?) do
      :error -> :ops
      :fatal -> :ops
      :unknown when legacy? -> :dev1
      :unknown -> :dev2
      _ -> false
    end
  end
end
