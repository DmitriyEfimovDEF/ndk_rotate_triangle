package com.example.myapplication

import android.graphics.Paint
import android.graphics.PixelFormat
import android.graphics.Rect
import android.opengl.GLES20
import android.opengl.GLSurfaceView
import android.os.Bundle
import android.util.Log
import android.view.LayoutInflater
import android.view.SurfaceHolder
import android.view.View
import android.view.ViewGroup
import androidx.core.content.ContextCompat
import androidx.fragment.app.Fragment
import com.example.myapplication.databinding.FragmentViewPagerItemBinding
import com.example.triangle.OnRadSetListener
import com.example.triangle.Triangle
import com.google.android.material.slider.Slider
import javax.microedition.khronos.egl.EGLConfig
import javax.microedition.khronos.opengles.GL10

class SurfaceFragment : Fragment(R.layout.fragment_view_pager_item) {

    private lateinit var triangle: Triangle
    private var binding: FragmentViewPagerItemBinding? = null
    private var angle: Float = 0F


    override fun onCreateView(
        inflater: LayoutInflater,
        container: ViewGroup?,
        savedInstanceState: Bundle?
    ) = FragmentViewPagerItemBinding.inflate(inflater, container, false).apply {
        binding = this
        initView(this)
    }.root

    private fun initView(binding: FragmentViewPagerItemBinding) {
        binding.surface.addView(GLSurfaceView(requireContext()).apply {
            setEGLContextClientVersion(2)
            setEGLContextFactory(ContextFactory())
            setRenderer(object : GLSurfaceView.Renderer {
                override fun onSurfaceCreated(gl: GL10?, config: EGLConfig?) {
//                    gl?.glClearColor(0.0f, 0.0f, 0.0f, 0.0f)
                    triangle = Triangle()//.apply { listeners.add(this@SurfaceFragment) }
                    triangle.draw(width.toFloat(), height.toFloat(), 3f, angle)
                }

                override fun onSurfaceChanged(gl: GL10?, width: Int, height: Int) {
                    gl?.glViewport(binding.surface.width, binding.surface.height, width, height)
                }

                override fun onDrawFrame(gl: GL10?) {
//                    gl?.glClear(1)
                    triangle.draw(width.toFloat(), height.toFloat(), 3f, angle)
                }
            })
            renderMode = GLSurfaceView.RENDERMODE_CONTINUOUSLY
        })

        binding.slider.addOnChangeListener(Slider.OnChangeListener { _, value, _ ->
            angle = value
        })
    }



    override fun onDestroy() {
        binding = null
        super.onDestroy()
    }

//    override fun onResume() {
//        super.onResume()
//        binding?.surface?.apply {
//            onResume()
//        }
//    }
//
//
//    override fun onPause() {
//        super.onPause()
//        binding?.surface?.apply {
//            onPause()
//        }
//    }
}