local map = ...
local game = map:get_game()

function map:on_started()

  local initial_x, initial_y = thrown_entity:get_position()
  thrown_entity:set_follow_streams(true)
  thrown_entity:set_can_traverse("stream", true)
  local movement = sol.movement.create("straight")
  movement:set_angle(3 * math.pi / 2)
  movement:set_speed(200)
  movement:set_smooth(false)
  movement:set_max_distance(160)
  movement:start(thrown_entity, function()
    local x, y = thrown_entity:get_position()
    assert(x < initial_x)  -- The stream should have had an influence.
    sol.main.exit()
  end)

end
