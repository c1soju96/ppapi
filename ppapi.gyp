# Copyright (c) 2010 The Chromium Authors. All rights reserved.
# Use of this source code is governed by a BSD-style license that can be
# found in the LICENSE file.


{
  'targets': [
    {
      'target_name': 'ppapi_c',
      'type': 'none',
      'direct_dependent_settings': {
        'include_dirs': [
           '..',
        ],
      },
      'sources': [
        'c/pp_event.h',
        'c/pp_instance.h',
        'c/pp_module.h',
        'c/pp_rect.h',
        'c/pp_resource.h',
        'c/pp_stdint.h',
        'c/pp_var.h',
        'c/ppb.h',
        'c/ppb_core.h',
        'c/ppb_device_context_2d.h',
        'c/ppb_image_data.h',
        'c/ppb_instance.h',
        'c/ppb_var.h',
        'c/ppp.h',
        'c/ppp_class.h',
        'c/ppp_instance.h',
      ],
    },
# TODO(brettw) this works in Linux but doesn't compile on Mac or Windows
# yet. The "cpp" project should also be separated out into a separate
#  project so that multiple plugins can just reference that.
# 
#    {
#      'target_name': 'ppapi_example',
#      'dependencies': [
#      ],
#      'include_dirs': [
#        '..',
#      ],
#      'xcode_settings': {
#        'INFOPLIST_FILE': 'Info.plist',
#      },
#      'sources': [
#        'example/example.cc',
#
#        'cpp/device_context_2d.cc',
#        'cpp/device_context_2d.h',
#        'cpp/image_data.cc',
#        'cpp/image_data.h',
#        'cpp/instance.cc',
#        'cpp/instance.h',
#        'cpp/module.cc',
#        'cpp/module.h',
#        'cpp/scriptable_object.cc',
#        'cpp/scriptable_object.h',
#        'cpp/rect.h',
#        'cpp/resource.cc',
#        'cpp/resource.h',
#        'cpp/var.cc',
#        'cpp/var.h',
#      ],
#      'conditions': [
#        ['OS=="win"', {
#          'product_name': 'ppapi_example',
#          'type': 'shared_library',
#          'msvs_guid': 'EE00E36E-9E8C-4DFB-925E-FBE32CEDB91B',
#          'sources': [
#            'example/ppapi_example.def',
#            'example/ppapi_example.rc',
#          ],
#          'run_as': {
#            'action': [
#              '<(PRODUCT_DIR)/<(EXECUTABLE_PREFIX)chrome<(EXECUTABLE_SUFFIX)',
#              '--no-sandbox',
#              '--internal-pepper',
#              '--enable-gpu-plugin',
#              '--load-plugin=$(TargetPath)',
#              'file://$(ProjectDir)test_page.html',
#            ],
#          },
#        }],
#        ['OS=="linux" or OS=="freebsd" or OS=="openbsd" or OS=="solaris"', {
#          'type': 'shared_library',
#          'cflags': ['-fvisibility=hidden'],
#          # -gstabs, used in the official builds, causes an ICE. Simply remove
#          # it.
#          'cflags!': ['-gstabs'],
#        }],
#        ['OS=="linux" or OS=="openbsd" or OS=="freebsd" and (target_arch=="x64" or target_arch=="arm") and linux_fpic!=1', {
#          'product_name': 'ppapi_example',
#          # Shared libraries need -fPIC on x86-64
#          'cflags': ['-fPIC'],
#        }, {
#          # Dependencies for all other OS/CPU combinations except those above
#          'dependencies': [
#          ],
#        }],
#        ['OS=="mac"', {
#          'type': 'loadable_module',
#          'mac_bundle': 1,
#          'product_name': 'PPAPIExample',
#          'product_extension': 'plucpgin',
#          'sources+': [
#            'example/Info.plist'
#          ],
#        }],
#      ],
#      # See README for instructions on how to run and debug on the Mac.
#      #'conditions' : [
#      #  ['OS=="mac"', {
#      #    'target_name' : 'Chromium',
#      #    'type' : 'executable',
#      #    'xcode_settings' : {
#      #      'ARGUMENTS' : '--renderer-startup-dialog --internal-pepper --no-sandbox file://${SRCROOT}/test_page.html'
#      #    },
#      #  }],
#      #],
#    },
  ],
}