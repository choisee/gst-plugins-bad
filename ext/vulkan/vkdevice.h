/*
 * GStreamer
 * Copyright (C) 2015 Matthew Waters <matthew@centricular.com>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 51 Franklin St, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 */

#ifndef _VK_DEVICE_H_
#define _VK_DEVICE_H_

#include <gst/gst.h>
#include "vk.h"

G_BEGIN_DECLS

#define GST_TYPE_VULKAN_DEVICE         (gst_vulkan_device_get_type())
#define GST_VULKAN_DEVICE(o)           (G_TYPE_CHECK_INSTANCE_CAST((o), GST_TYPE_VULKAN_DEVICE, GstVulkanDevice))
#define GST_VULKAN_DEVICE_CLASS(k)     (G_TYPE_CHECK_CLASS_CAST((k), GST_TYPE_VULKAN_DEVICE, GstVulkanDeviceClass))
#define GST_IS_VULKAN_DEVICE(o)        (G_TYPE_CHECK_INSTANCE_TYPE((o), GST_TYPE_VULKAN_DEVICE))
#define GST_IS_VULKAN_DEVICE_CLASS(k)  (G_TYPE_CHECK_CLASS_TYPE((k), GST_TYPE_VULKAN_DEVICE))
#define GST_VULKAN_DEVICE_GET_CLASS(o) (G_TYPE_INSTANCE_GET_CLASS((o), GST_TYPE_VULKAN_DEVICE, GstVulkanDeviceClass))
GType gst_vulkan_device_get_type       (void);

struct _GstVulkanDevice
{
  GstObject parent;

  GstVulkanInstance *instance;

  guint device_index;
  VkDevice device; /* hides a pointer */
  VkPhysicalDeviceProperties gpu_props;
  VkPhysicalDeviceFeatures gpu_features;
  VkPhysicalDeviceMemoryProperties memory_properties;

  VkQueueFamilyProperties *queue_family_props;
  guint32 n_queue_families;

  guint32 queue_family_id;
  guint32 n_queues;

  VkCmdPool cmd_pool;
};

struct _GstVulkanDeviceClass
{
  GstObjectClass parent_class;
};

GstVulkanDevice *   gst_vulkan_device_new                   (GstVulkanInstance * instance);
GstVulkanInstance * gst_vulkan_device_get_instance           (GstVulkanDevice * device);
gboolean            gst_vulkan_device_open                  (GstVulkanDevice * device,
                                                             GError ** error);
void                gst_vulkan_device_close                 (GstVulkanDevice * device);

gpointer            gst_vulkan_device_get_proc_address      (GstVulkanDevice * device,
                                                             const gchar * name);
GstVulkanQueue *    gst_vulkan_device_get_queue             (GstVulkanDevice * device,
                                                             guint32 queue_family,
                                                             guint32 queue_i,
                                                             GError ** error);
VkPhysicalDevice    gst_vulkan_device_get_physical_device   (GstVulkanDevice * device);
gboolean            gst_vulkan_device_create_cmd_buffer     (GstVulkanDevice * device,
                                                             VkCmdBuffer * cmd,
                                                             GError ** error);

G_END_DECLS

#endif /* _VK_DEVICE_H_ */