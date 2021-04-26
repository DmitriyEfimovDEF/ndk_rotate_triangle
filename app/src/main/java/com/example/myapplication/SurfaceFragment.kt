package com.example.myapplication

import android.opengl.GLSurfaceView
import android.os.Bundle
import android.view.LayoutInflater
import android.view.ViewGroup
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

    @Volatile
    private var angle: Float = 0F

    private val callback = object : OnRadSetListener{
        override fun onRadSetCall(rad: Float) {
            requireActivity().runOnUiThread() {
                binding?.tv?.text = rad.toString()
            }
        }
    }

    override fun onCreateView(
        inflater: LayoutInflater,
        container: ViewGroup?,
        savedInstanceState: Bundle?
    ) = FragmentViewPagerItemBinding.inflate(inflater, container, false).apply {
        binding = this
        initView()
    }.root

    private fun initView() {
        binding?.surface?.apply {
            setEGLContextClientVersion(2)
            setRenderer(object : GLSurfaceView.Renderer {
                override fun onSurfaceCreated(gl: GL10?, config: EGLConfig?) {
                    triangle = Triangle().also { it.onRadSet(callback) }
                }

                override fun onSurfaceChanged(gl: GL10?, width: Int, height: Int) {}

                override fun onDrawFrame(gl: GL10?) {
                    triangle.draw(width.toFloat(), height.toFloat(), 0f, angle)
                }
            })
            renderMode = GLSurfaceView.RENDERMODE_CONTINUOUSLY
        }

        binding?.slider?.addOnChangeListener(Slider.OnChangeListener { _, value, _ ->
            angle = value
        })
    }

    override fun onResume() {
        super.onResume()
        binding?.surface?.onResume()

    }

    override fun onPause() {
        super.onPause()
        binding?.surface?.onPause()
    }

    override fun onDestroy() {
        binding = null
        super.onDestroy()
    }
}