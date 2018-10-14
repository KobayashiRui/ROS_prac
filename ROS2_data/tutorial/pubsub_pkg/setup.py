from setuptools import setup

package_name = 'pubsub_pkg'

setup(
    name=package_name,
    version='0.0.0',
    packages=[],
    py_modules=[
        'pub_node'],
    data_files=[],
    install_requires=['setuptools'],
    zip_safe=True,
    author='RuiKobayashi',
    author_email='hoge@hoge.com',
    maintainer='RuiKobayashi',
    maintainer_email='hoge@hoge.com',
    keywords=['ROS'],
    classifiers=[
        'Intended Audience :: Developers',
        'License :: OSI Approved :: Apache Software License',
        'Programming Language :: Python',
        'Topic :: Software Development',
    ],
    description='ROS2 pubsub package.',
    license='Apache License, Version 2.0',
    tests_require=['pytest'],
    entry_points={
        'console_scripts': [
            'pub_node = pub_node:main',
        ],
    },
)
