-- Lua script of map bugs/1552_entire_savegame_access.

local map = ...

function map:on_started()
  local game = map:get_game()
  -- Fill the savegame normally:
  game:set_value("first", true)
  game:set_value("second", 2)
  game:set_value("third", "three")

  local save = game:get_values()
  local count = 0
  for key, value in pairs(save) do
    count = count + 1
    if "first" == key then
      assert_equal(value, true)
    elseif "second" == key then
      assert_equal(value, 2)
    elseif "third" == key then
      assert_equal(value, "three")
    else
      error("Unexpected savegame key: " .. key)
    end
  end
  assert_equal(count, 3, "Repeated or missing savegame key.")

  sol.main.exit()
end
