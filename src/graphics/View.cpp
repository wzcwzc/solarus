/*
 * Copyright (C) 2018-2020 std::gregwar, Solarus - http://www.solarus-games.org
 *
 * Solarus is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Solarus is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */
#include "solarus/graphics/View.h"
#include "glm/gtc/matrix_inverse.hpp"
#include "glm/gtc/matrix_transform.hpp"

namespace Solarus {

View::View(const glm::vec2& size) : View(size/2.f, size) {

}

View::View(const Rectangle& rect)
  : viewport(0.f,0.f,1.f,1.f)
{
  reset(rect);
}

View::View(const glm::vec2& center, const glm::vec2& size) :
  center(center),
  size(size),
  rotation(0),
  viewport(0.f,0.f,1.f,1.f)
{

}

glm::vec2 View::get_center() const {
  return center;
}

glm::vec2 View::get_size() const {
  return size;
}

float View::get_rotation() const {
  return rotation;
}

void View::set_center(const glm::vec2& center) {
  this->center = center;
  invalidate();
}

void View::set_size(const glm::vec2& size) {
  this->size = size;
  invalidate();
}

void View::set_rotation(float rotation) {
  this->rotation = rotation;
  invalidate();
}

void View::move(const glm::vec2& delta) {
  center += delta;
  invalidate();
}

void View::zoom(const glm::vec2& factor) {
  size /= factor;
  invalidate();
}

void View::rotate(float rotation) {
  this->rotation += rotation;
  invalidate();
}

const glm::mat4& View::get_transform() const {
  if(transform_dirty) {
    auto view =
            glm::translate(
              glm::rotate(
                glm::mat4(1.f),
                  rotation,
                  glm::vec3(0.f,0.f,-1.f)
                ),
              glm::vec3(-center, 0.f)
            );
    transform = glm::ortho<float>(-size.x*0.5f, size.x*0.5f, -size.y*0.5f, size.y*0.5f)*view;
    transform_dirty = false;
  }
  return transform;
}

const glm::mat4& View::get_inverse_transform() const {
  if(inv_transform_dirty) {
    inv_transform = glm::inverse(get_transform());
    inv_transform_dirty = false;
  }
  return inv_transform;
}

void View::set_transform(const glm::mat4& transform) {
  this->transform = transform;
  transform_dirty = false;
  inv_transform_dirty = true;
}

void View::set_viewport(const FRectangle& viewport) {
  this->viewport = viewport;
}

const FRectangle& View::get_viewport() const {
  return viewport;
}

void View::reset(const Rectangle &rect) {
  center = rect.get_center();
  size = rect.get_size();
  rotation = 0.f;
  invalidate();
}

}