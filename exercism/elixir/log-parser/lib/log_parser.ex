defmodule LogParser do
  def valid_line?(line) do
    line =~ ~r/^\[DEBUG\]|\[INFO\]|\[WARNING\]|\[ERROR\]/
  end

  def split_line(line) do
    String.split(line, ~r/<[~*=-]*>/)
  end

  def remove_artifacts(line) do
    String.replace(line, ~r/end-of-line\d+/i, "")
  end

  def tag_with_user_name(line) do
    if line =~ ~r/User/ do
      [_, name] = Regex.run(~r/User[\s\t]+(\S+)/, line)
      "[USER] #{name} " <> line
    else
      line
    end
  end
end
