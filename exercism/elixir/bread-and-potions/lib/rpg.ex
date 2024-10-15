defmodule RPG do
  defprotocol Edible do
    def eat(a, b)
  end

  defmodule Character do
    defstruct health: 100, mana: 0
  end

  defmodule LoafOfBread do
    defstruct []
  end

  defimpl Edible, for: LoafOfBread do
    def eat(_, %Character{health: health} = character) do
      {nil, %{character | health: health + 5}}
    end
  end

  defmodule ManaPotion do
    defstruct strength: 10
  end

  defmodule EmptyBottle do
    defstruct []
  end

  defmodule Poison do
    defstruct []
  end

  defimpl Edible, for: ManaPotion do
    def eat(%ManaPotion{strength: strength}, %Character{mana: mana} = memes) do
      {%EmptyBottle{}, %{memes | mana: mana + strength}}
    end
  end

  defimpl Edible, for: Poison do
    def eat(_, %Character{} = memes) do
      {%EmptyBottle{}, %{memes | health: 0}}
    end
  end
end
