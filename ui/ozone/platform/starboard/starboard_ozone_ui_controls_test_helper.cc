// Copyright 2024 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "ui/ozone/platform/starboard/starboard_ozone_ui_controls_test_helper.h"

#include "ui/aura/window_tree_host.h"

namespace ui {

StarboardOzoneUIControlsTestHelper:: ~StarboardOzoneUIControlsTestHelper() {

}

void StarboardOzoneUIControlsTestHelper::Reset() {}

bool StarboardOzoneUIControlsTestHelper::SupportsScreenCoordinates() const {
  return true;
}

unsigned StarboardOzoneUIControlsTestHelper::ButtonDownMask() const {
  // dummy
  return 123;
}

void StarboardOzoneUIControlsTestHelper::SendKeyEvents(gfx::AcceleratedWidget widget,
                                                 ui::KeyboardCode key,
                                                 int key_event_types,
                                                 int accelerator_state,
                                                 base::OnceClosure closure) {
}

void StarboardOzoneUIControlsTestHelper::SendMouseMotionNotifyEvent(
    gfx::AcceleratedWidget widget,
    const gfx::Point& mouse_loc,
    const gfx::Point& mouse_loc_in_screen,
    base::OnceClosure closure) {
}

void StarboardOzoneUIControlsTestHelper::SendMouseEvent(
    gfx::AcceleratedWidget widget,
    ui_controls::MouseButton type,
    int button_state,
    int accelerator_state,
    const gfx::Point& mouse_loc,
    const gfx::Point& mouse_loc_in_screen,
    base::OnceClosure closure) {

}

void StarboardOzoneUIControlsTestHelper::RunClosureAfterAllPendingUIEvents(
    base::OnceClosure closure) {
}

bool StarboardOzoneUIControlsTestHelper::MustUseUiControlsForMoveCursorTo() {
  return false;
}

OzoneUIControlsTestHelper* CreateOzoneUIControlsTestHelperStarboard() {
  return new StarboardOzoneUIControlsTestHelper();
}


}  // namespace ui
