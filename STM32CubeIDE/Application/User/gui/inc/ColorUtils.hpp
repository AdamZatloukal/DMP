/*
 * ColorUtils.hpp
 *
 *  Created on: Dec 29, 2024
 *      Author: Adam Zatloukal
 */

#ifndef APPLICATION_USER_GUI_COLORUTILS_HPP_
#define APPLICATION_USER_GUI_COLORUTILS_HPP_


#include <touchgfx/Color.hpp>
#include <touchgfx/widgets/Box.hpp>	// To access the Box object
#include <touchgfx/widgets/canvas/Circle.hpp>
#include <touchgfx/widgets/canvas/PainterRGB565.hpp>

void setBoxColor(touchgfx::Box& box, uint8_t player);
void setCircleColor(touchgfx::PainterRGB565& circle_painter,touchgfx::Circle& circle, uint8_t player);


#endif /* APPLICATION_USER_GUI_COLORUTILS_HPP_ */
