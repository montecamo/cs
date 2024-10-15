defmodule BoutiqueSuggestions do
  def get_combinations(tops, bottoms, options \\ []) do
    max = options[:maximum_price] || 100

    for x <- tops,
        y <- bottoms,
        x.base_color != y.base_color,
        x.price + y.price <= max do
      {x, y}
    end
  end
end
