defmodule BoutiqueInventory do
  def sort_by_price(inventory) do
    inventory
    |> Enum.sort_by(
      fn %{:price => price} ->
        price
      end,
      :asc
    )
  end

  def with_missing_price(inventory) do
    inventory |> Enum.filter(fn %{:price => price} -> price == nil end)
  end

  def update_names(inventory, old_word, new_word) do
    inventory
    |> Enum.map(&Map.update!(&1, :name, fn s -> String.replace(s, old_word, new_word) end))
  end

  def increase_quantity(item, count) do
    Map.update!(item, :quantity_by_size, fn s ->
      s
      |> Enum.map(fn {key, value} -> {key, value + count} end)
      |> Map.new()
    end)
  end

  def total_quantity(item) do
    item.quantity_by_size
    |> Map.values()
    |> Enum.reduce(0, &+/2)
  end
end
