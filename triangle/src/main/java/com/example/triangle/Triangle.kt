package com.example.triangle

class Triangle {

    external fun draw(width: Float, height: Float, scale: Float, angle: Float)
    external fun onRadSet(listener: OnRadSetListener)

    companion object {
        init {
            System.loadLibrary("Triangle")
        }
    }
}

interface OnRadSetListener {

    fun onRadSetCall(rad: Float)
}